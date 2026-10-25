#include "Cluster_Assignment.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {
int checks = 0;
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) { std::cerr << "FAIL: " << message << "\n"; std::exit(1); }
}
template <typename Exception, typename Function>
void throws(Function action, const char* message) {
    bool caught = false;
    try { action(); } catch (const Exception&) { caught = true; }
    require(caught, message);
}
}

int main() {
    using Dataset = ClusterAssignment::Dataset;

    Dataset data{{0, 0}, {1, 1}, {10, 10}, {11, 11}};
    Dataset centroids{{0, 0}, {10, 10}};
    auto result = ClusterAssignment::assignClusters(data, centroids);
    require(result.size() == data.size(), "one label per point");
    require(result == std::vector<int>({0, 0, 1, 1}), "two obvious clusters");

    // a point exactly on a centroid goes to that centroid
    require(ClusterAssignment::assignClusters({{10, 10}}, centroids)[0] == 1, "point on centroid");

    // tie: equally close to both centroids -> lower index wins
    require(ClusterAssignment::assignClusters({{5, 5}}, centroids)[0] == 0, "tie goes to lower index");

    // one centroid: everything belongs to cluster 0
    auto single = ClusterAssignment::assignClusters(data, Dataset{{3, 3}});
    require(single == std::vector<int>({0, 0, 0, 0}), "single centroid");

    // 1-D data and order of centroids matters for labels
    auto oneD = ClusterAssignment::assignClusters({{1}, {9}}, Dataset{{10}, {0}});
    require(oneD == std::vector<int>({1, 0}), "1-D data, labels follow centroid order");

    // negative coordinates
    auto neg = ClusterAssignment::assignClusters({{-4, -4}, {4, 4}}, Dataset{{-5, -5}, {5, 5}});
    require(neg == std::vector<int>({0, 1}), "negative coordinates");

    // input is not modified
    Dataset dataCopy = data;
    ClusterAssignment::assignClusters(data, centroids);
    require(data == dataCopy, "data unchanged");

    throws<std::invalid_argument>([&] { ClusterAssignment::assignClusters(data, Dataset{}); }, "empty centroids");
    throws<std::invalid_argument>([&] { ClusterAssignment::assignClusters(Dataset{}, centroids); }, "empty data");
    throws<std::invalid_argument>([&] { ClusterAssignment::assignClusters(data, Dataset{{1, 2, 3}}); }, "dimension mismatch");

    std::cout << "All " << checks << " checks passed.\n";
    return 0;
}
