
#ifndef CLUSTER_ASSIGNMENT_HPP
#define CLUSTER_ASSIGNMENT_HPP

#include "k_means/Distance_Calculation.hpp"
#include <vector>
#include <stdexcept>

class ClusterAssignment {
public:
    // Define a single data point and a collection of data points.
    using Point = std::vector<double>;
    using Dataset = std::vector<Point>;

    /*
     * Assign each data point to its nearest centroid.
     *
     * Parameters:
     *   data      - The dataset containing the data points.
     *   centroids - The dataset containing the cluster centroids.
     *
     * Returns:
     *   A vector of integers representing the cluster index
     *   assigned to each data point.
     *
     * Rules:
     *   1. Each point is assigned to its nearest centroid.
     *   2. If distances are equal, the centroid with the
     *      smallest index is selected.
     *   3. An exception is thrown if either dataset is empty
     *      or if point and centroid dimensions do not match.
     */
    static std::vector<int> assignClusters(
        const Dataset& data,
        const Dataset& centroids
    );

    // Prevent object creation because all operations are static.
    ClusterAssignment() = delete;
};

#endif // CLUSTER_ASSIGNMENT_HPP
