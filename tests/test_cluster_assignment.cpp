#include "k_means/ClusterAssignment.hpp"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace {

int checks = 0;
int failures = 0;

void require(bool condition, std::string_view message) {
    ++checks;
    if (!condition) {
        ++failures;
        std::cerr << "FAIL: " << message << '\n';
    }
}

template <typename Exception, typename Function>
void throws(Function&& action, std::string_view message) {
    bool caught = false;
    try {
        action();
    } catch (const Exception&) {
        caught = true;
    } catch (...) {
        // Wrong exception type — fall through with caught == false.
    }
    require(caught, message);
}

}  // namespace

int main() {
    using Dataset = ClusterAssignment::Dataset;
    using Labels = std::vector<int>;

    // --- Two obvious clusters -------------------------------------------------
    const Dataset data{{0, 0}, {1, 1}, {10, 10}, {11, 11}};
    const Dataset centroids{{0, 0}, {10, 10}};

    const auto result = ClusterAssignment::assignClusters(data, centroids);
    require(result.size() == data.size(), "one label per point");
    require(result == Labels({0, 0, 1, 1}), "two obvious clusters");

    // --- Boundary cases -------------------------------------------------------
    require(ClusterAssignment::assignClusters({{10, 10}}, centroids)[0] == 1,
            "point exactly on a centroid goes to that centroid");

    require(ClusterAssignment::assignClusters({{5, 5}}, centroids)[0] == 0,
            "tie between centroids resolves to lower index");

    const auto single = ClusterAssignment::assignClusters(data, Dataset{{3, 3}});
    require(single == Labels({0, 0, 0, 0}), "single centroid assigns all to cluster 0");

    // --- Geometry: 1-D and negative coordinates -------------------------------
    const auto oneD = ClusterAssignment::assignClusters({{1}, {9}}, Dataset{{10}, {0}});
    require(oneD == Labels({1, 0}), "1-D data: labels follow centroid order");

    const auto neg = ClusterAssignment::assignClusters({{-4, -4}, {4, 4}},
                                                       Dataset{{-5, -5}, {5, 5}});
    require(neg == Labels({0, 1}), "negative coordinates handled correctly");

    // --- Input immutability ---------------------------------------------------
    const Dataset dataCopy = data;
    (void)ClusterAssignment::assignClusters(data, centroids);
    require(data == dataCopy, "input data is not modified");

    // --- Error handling -------------------------------------------------------
    throws<std::invalid_argument>(
        [&] { (void)ClusterAssignment::assignClusters(data, Dataset{}); },
        "empty centroids throws invalid_argument");

    throws<std::invalid_argument>(
        [&] { (void)ClusterAssignment::assignClusters(Dataset{}, centroids); },
        "empty data throws invalid_argument");

    throws<std::invalid_argument>(
        [&] { (void)ClusterAssignment::assignClusters(data, Dataset{{1, 2, 3}}); },
        "dimension mismatch throws invalid_argument");

    throws<std::invalid_argument>(
        [] { (void)ClusterAssignment::assignClusters({{1, 2}, {3}}, {{0, 0}}); },
        "ragged data throws invalid_argument");

    throws<std::invalid_argument>(
        [] { (void)ClusterAssignment::assignClusters({{1, 2}}, {{0, std::numeric_limits<double>::quiet_NaN()}}); },
        "non-finite centroid throws invalid_argument");

    // --- Summary --------------------------------------------------------------
    if (failures == 0) {
        std::cout << "All " << checks << " checks passed.\n";
        return EXIT_SUCCESS;
    }
    std::cerr << failures << " of " << checks << " checks failed.\n";
    return EXIT_FAILURE;
}
