#include "Cluster_Assignment.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>

std::vector<int> ClusterAssignment::assignClusters(const Dataset& data,
                                                   const Dataset& centroids)
{
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty.");
    }
    if (centroids.empty()) {
        throw std::invalid_argument("Centroids must not be empty.");
    }

    std::vector<int> assignments(data.size());
    for (std::size_t i = 0; i < data.size(); ++i) {
        double minDistance = std::numeric_limits<double>::max();
        int bestCluster = 0;
        for (std::size_t j = 0; j < centroids.size(); ++j) {
            // Squared distance is enough: it picks the same nearest centroid
            double d = DistanceCalculator::squareddistance(data[i], centroids[j]);
            if (d < minDistance) {
                minDistance = d;
                bestCluster = static_cast<int>(j);
            }
        }
        assignments[i] = bestCluster;
    }
    return assignments;
}
