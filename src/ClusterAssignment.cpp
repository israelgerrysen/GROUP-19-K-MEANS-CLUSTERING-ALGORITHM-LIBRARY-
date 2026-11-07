#include "k_means/ClusterAssignment.hpp"
#include "k_means/Distance_Calculation.hpp"
#include <limits>
#include <stdexcept>

// Assign each point to its nearest centroid.
// We compare squared distances, no sqrt() needed -
// the smallest squared distance is also the smallest real distance.
std::vector<int> ClusterAssignment::assignClusters(
    const Dataset& data, const Dataset& centroids)
{
    // 1. Guard against bad input
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty.");
    }
    if (centroids.empty()) {
        throw std::invalid_argument("Centroids must not be empty.");
    }

    // 2. Prepare result: one slot per point
    std::vector<int> assignments;
    assignments.reserve(data.size());

    // 3. For each point, find its nearest centroid
    for (const Point& point : data) {
        double bestDistance = std::numeric_limits<double>::max();
        int bestCluster = 0;

        for (size_t j = 0; j < centroids.size(); ++j) {
            double distance = DistanceCalculator::squaredDistance(point, centroids[j]);

            // Use < not <= so ties keep the FIRST centroid (lowest index)
            if (distance < bestDistance) {
                bestDistance = distance;
                bestCluster = static_cast<int>(j);
            }
        }

        assignments.push_back(bestCluster);
    }

    return assignments;
}