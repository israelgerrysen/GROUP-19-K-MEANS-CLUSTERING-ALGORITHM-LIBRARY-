#include "k_means/Centroid_initialization.hpp"

#include <cassert>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>

int main() {
    using Dataset = CentroidInitializer::Dataset;
    const Dataset data{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    auto throws = [](auto&& action) {
        try { action(); } catch (const std::invalid_argument&) { return true; }
        return false;
    };

    assert(throws([] { CentroidInitializer invalid(0); }));
    assert(throws([] { CentroidInitializer invalid(-1); }));
    assert(throws([&] { CentroidInitializer(2).initialize({}); }));
    assert(throws([&] { CentroidInitializer(6).initialize(data); }));
    assert(throws([&] { CentroidInitializer(1).initialize({{1, 2}, {3}}); }));
    assert(throws([&] { CentroidInitializer(1).initialize({{1, std::numeric_limits<double>::infinity()}}); }));

    const Dataset centroids = CentroidInitializer(3, 42).initialize(data);
    const std::set<std::vector<double>> unique(centroids.begin(), centroids.end());
    const std::set<std::vector<double>> original(data.begin(), data.end());
    assert(centroids.size() == 3 && unique.size() == 3);
    for (const auto& point : centroids) assert(original.count(point) == 1);
    assert(CentroidInitializer(5, 42).initialize(data).size() == data.size());
    assert(centroids == CentroidInitializer(3, 42).initialize(data));

    CentroidInitializer init(3, 42);
    assert(init.getK() == 3);
    init.setK(2);
    assert(init.getK() == 2 && init.initialize(data).size() == 2);
    assert(throws([&] { init.setK(0); }));
    assert(init.getK() == 2); // rejected setter leaves state unchanged

    std::cout << "Centroid initialization checks passed.\n";
}
