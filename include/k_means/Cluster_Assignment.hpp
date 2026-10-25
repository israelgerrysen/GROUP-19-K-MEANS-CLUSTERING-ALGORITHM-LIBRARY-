#ifndef CLUSTER_ASSIGNMENT_HPP
#define CLUSTER_ASSIGNMENT_HPP
#include "Distance_Calculation.hpp"
#include <vector>

// Assigns each data point to its nearest centroid.
// All functions are static, so no object is needed:
//     ClusterAssignment::assignClusters(data, centroids);
class ClusterAssignment {
public:
    using Point   = std::vector<double>;
    using Dataset = std::vector<Point>;

    // Returns, for every point in data, the index of its closest centroid.
    // Ties go to the centroid with the lower index.
    // Throws std::invalid_argument if data or centroids are empty, or if a
    // point and a centroid have different dimensions.
    static std::vector<int> assignClusters(const Dataset& data,
                                           const Dataset& centroids);

    // This is a utility class, so objects cannot be created.
    ClusterAssignment() = delete;
};

#endif // CLUSTER_ASSIGNMENT_HPP
