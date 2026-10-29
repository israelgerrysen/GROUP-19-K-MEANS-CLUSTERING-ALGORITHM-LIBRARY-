#include <k_means/k_means.hpp>

#include <exception>
#include <filesystem>
#include <iostream>
#include <string>
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
    // Missing goal values are imputed before fitting the scaler and clustering.
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

    // Compute final labels and inertia using the same final scaled centroids.
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

int main(int argc, char* argv[]) {
    // The bundled CSV stores home and away goal counts in zero-based columns 12 and 13.
    // A custom CSV path can be supplied as the first command-line argument.
    std::string filename = argc > 1 ? argv[1] : "data/input/football.csv";
    if (argc == 1 && !std::filesystem::exists(filename)) {
        for (const auto& candidate : std::vector<std::string>{
                 "../data/input/football.csv", "../../data/input/football.csv"}) {
            if (std::filesystem::exists(candidate)) {
                filename = candidate;
                break;
            }
        }
    }

    try {
        const auto data = DataLoader::loadCSV(filename, {12, 13});
        if (data.empty()) {
            std::cerr << "The selected CSV columns contain no data rows.\n";
            return 1;
        }

        const auto result = cluster(data, 3, 42U);
        std::cout << "Loaded " << data.size()
                  << " matches using home and away goals from " << filename << ".\n";
        printResult(result);

        std::vector<std::size_t> counts(result.centroids.size(), 0);
        for (const int label : result.labels) ++counts[static_cast<std::size_t>(label)];
        for (std::size_t clusterIndex = 0; clusterIndex < counts.size(); ++clusterIndex)
            std::cout << "Matches in cluster " << clusterIndex << ": " << counts[clusterIndex] << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Could not cluster CSV data: " << error.what() << '\n';
        return 1;
    }
}
