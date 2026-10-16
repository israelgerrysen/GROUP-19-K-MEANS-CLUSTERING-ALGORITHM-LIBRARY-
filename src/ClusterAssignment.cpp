
#include "Cluster_Assignment.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>

// Assign each data point to its nearest cluster centroid.
std::vector<int> ClusterAssignment::assignClusters(
    const Dataset& data,
    const Dataset& centroids)
{
    // Ensure that the dataset contains data points.
    if (data.empty()) {
        throw std::invalid_argument(
            "Data must not be empty."
        );
    }

    // Ensure that at least one centroid is available.
    if (centroids.empty()) {
        throw std::invalid_argument(
            "Centroids must not be empty."
        );
    }

    // Store the cluster index assigned to each data point.
    std::vector<int> assignments(data.size());

    // Process each data point in the dataset.
    for (std::size_t i = 0; i < data.size(); ++i) {
        double minimumDistance =
            std::numeric_limits<double>::max();

        int nearestCluster = 0;

        // Compare the current point with every centroid.
        for (std::size_t j = 0; j < centroids.size(); ++j) {
            double distance =
                DistanceCalculator::squareddistance(
                    data[i],
                    centroids[j]
                );

            // Update the nearest cluster when a shorter
            // distance is found.
            if (distance < minimumDistance) {
                minimumDistance = distance;
                nearestCluster = static_cast<int>(j);
            }
        }

        // Save the nearest centroid's index.
        assignments[i] = nearestCluster;
    }

    // Return the cluster assignments for all data points.
    return assignments;
}
