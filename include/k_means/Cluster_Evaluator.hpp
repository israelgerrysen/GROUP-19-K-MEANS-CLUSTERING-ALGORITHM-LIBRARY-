// API for evaluating a completed clustering with within-cluster sum of squared distances (inertia).
// Labels are indexed per input point and refer to entries in the supplied centroid list.
#ifndef K_MEANS_CLUSTER_EVALUATOR_HPP
#define K_MEANS_CLUSTER_EVALUATOR_HPP

#include <vector>

class ClusterEvaluator {
public:
    using Point = std::vector<double>;
    using Dataset = std::vector<Point>;

    // Sum of squared distances from each point to its assigned centroid.
    // Throws std::invalid_argument for malformed or inconsistent inputs.
    static double computeInertia(const Dataset& points,
                                 const std::vector<int>& labels,
                                 const Dataset& centroids);
    ClusterEvaluator() = delete;
};

#endif // K_MEANS_CLUSTER_EVALUATOR_HPP
