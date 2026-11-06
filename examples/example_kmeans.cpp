#include <k_means/k_means.hpp>

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace {
using Dataset = std::vector<std::vector<double>>;

struct ClusteringResult {
    Dataset centroids;
    std::vector<int> labels;
    double inertia;
    int iterations;
};

ClusteringResult cluster(const Dataset& rawData, int k, unsigned int seed) {
    // Impute the example's missing value, then scale both features before
    // using Euclidean distance so neither feature dominates by range alone.
    Dataset data = rawData;
    DataPreprocessor::fillMissingWithMedian(data);
    FeatureScaler scaler;
    const Dataset scaledData = scaler.fit_transform(data);

    CentroidInitializer initializer(k, seed);
    Dataset centroids = initializer.initialize(scaledData);
    ConvergenceDetector convergence(1e-6, 100);
    std::vector<int> previousLabels;
    int iterations = 0;

    for (int iteration = 1; iteration <= convergence.getMaxIterations(); ++iteration) {
        const Dataset previousCentroids = centroids;
        auto labels = ClusterAssignment::assignClusters(scaledData, previousCentroids);
        handleEmptyClusters(scaledData, centroids, labels);
        auto nextCentroids = CentroidUpdater::update(scaledData, labels, centroids);
        const bool stop = convergence.shouldStop(
            previousCentroids, nextCentroids, previousLabels, labels, iteration);
        centroids = std::move(nextCentroids);
        previousLabels = std::move(labels);
        iterations = iteration;
        if (stop) break;
    }

    // Reassign after the final centroid update so labels and inertia match it.
    auto labels = ClusterAssignment::assignClusters(scaledData, centroids);
    const double inertia = ClusterEvaluator::computeInertia(scaledData, labels, centroids);
    return {scaler.inverse_transform(centroids), std::move(labels), inertia, iterations};
}

void printResult(const ClusteringResult& result) {
    std::cout << "Iterations: " << result.iterations << '\n'
              << "Inertia (scaled feature space): " << result.inertia << '\n';
    for (std::size_t cluster = 0; cluster < result.centroids.size(); ++cluster) {
        std::cout << "Cluster " << cluster << " centroid: (";
        for (std::size_t feature = 0; feature < result.centroids[cluster].size(); ++feature) {
            if (feature != 0) std::cout << ", ";
            std::cout << result.centroids[cluster][feature];
        }
        std::cout << ")\n";
    }
}
} // namespace

int main() {
    // Two clear groups, plus one missing feature to demonstrate imputation.
    const Dataset data{
        {1.0, 1.0}, {1.2, 0.8}, {0.8, 1.1}, {1.1, 1.3},
        {8.0, 8.0}, {8.2, 7.8}, {7.8, 8.1}, {8.1, 8.3},
        {1.0, std::numeric_limits<double>::quiet_NaN()}
    };

    try {
        const auto result = cluster(data, 2, 42U);
        printResult(result);
        std::cout << "Point cluster labels: ";
        for (std::size_t i = 0; i < result.labels.size(); ++i) {
            if (i != 0) std::cout << ' ';
            std::cout << result.labels[i];
        }
        std::cout << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Clustering failed: " << error.what() << '\n';
        return 1;
    }
}
