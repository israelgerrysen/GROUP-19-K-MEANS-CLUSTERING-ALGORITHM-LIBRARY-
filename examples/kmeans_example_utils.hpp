#ifndef KMEANS_EXAMPLE_UTILS_HPP
#define KMEANS_EXAMPLE_UTILS_HPP

#include "k_means/Centroid_Update.hpp"
#include "k_means/Centroid_initialization.hpp"
#include "k_means/ClusterAssignment.hpp"
#include "k_means/Cluster_Evaluator.hpp"
#include "k_means/ConvergenceDetector.hpp"
#include "k_means/DataPreprocessor.hpp"
#include "k_means/EmptyCluster.hpp"
#include "k_means/feature_scaler.hpp"

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

namespace kmeans_example {
using Dataset = CentroidInitializer::Dataset;

struct Result {
    Dataset centroids;
    std::vector<int> labels;
    double inertia;
    int iterations;
};

inline Result cluster(const Dataset& rawData, int k, unsigned int seed = 42) {
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

    // Recompute labels against the final centroids before evaluating the result.
    auto labels = ClusterAssignment::assignClusters(scaledData, centroids);
    const double inertia = ClusterEvaluator::computeInertia(scaledData, labels, centroids);
    return {scaler.inverse_transform(centroids), std::move(labels), inertia, iterations};
}

inline void printResult(const Result& result, std::ostream& output = std::cout) {
    output << "Iterations: " << result.iterations << '\n';
    output << "Inertia (scaled feature space): " << result.inertia << '\n';
    for (std::size_t c = 0; c < result.centroids.size(); ++c) {
        output << "Cluster " << c << " centroid: (";
        for (std::size_t d = 0; d < result.centroids[c].size(); ++d) {
            if (d != 0) output << ", ";
            output << result.centroids[c][d];
        }
        output << ")\n";
    }
}
}

#endif // KMEANS_EXAMPLE_UTILS_HPP
