#include "k_means/Cluster_Evaluator.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

int main() {
    using Dataset = ClusterEvaluator::Dataset;
    const Dataset points{{1, 1}, {2, 2}, {8, 8}, {9, 9}};
    const Dataset centroids{{1.5, 1.5}, {8.5, 8.5}};
    const std::vector<int> labels{0, 0, 1, 1};
    const double inertia = ClusterEvaluator::computeInertia(points, labels, centroids);
    assert(std::abs(inertia - 2.0) < 1e-12);
    assert(ClusterEvaluator::computeInertia({{3}}, {0}, {{3}}) == 0.0);

    auto throws = [](auto&& action) {
        try { action(); } catch (const std::invalid_argument&) { return true; }
        return false;
    };
    assert(throws([] { ClusterEvaluator::computeInertia({}, {}, {{0}}); }));
    assert(throws([&] { ClusterEvaluator::computeInertia(points, {0}, centroids); }));
    assert(throws([&] { ClusterEvaluator::computeInertia(points, {0, 0, 1, 2}, centroids); }));
    assert(throws([&] { ClusterEvaluator::computeInertia(points, labels, {{0}, {1}}); }));
    assert(throws([] { ClusterEvaluator::computeInertia({{0, std::numeric_limits<double>::quiet_NaN()}}, {0}, {{0, 0}}); }));
    std::cout << "Cluster evaluation checks passed.\n";
}
