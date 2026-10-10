
#include "Centroid_initialization.hpp"
#include <cassert>
#include <iostream>
#include <set>

using Dataset = CentroidInitializer::Dataset;

int main() {
    Dataset data = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

    // Invalid input returns empty
    assert(CentroidInitializer(2).initialize({}).empty());
    assert(CentroidInitializer(0).initialize(data).empty());
    assert(CentroidInitializer(-1).initialize(data).empty());
    assert(CentroidInitializer(6).initialize(data).empty());

    // Valid input: k centroids, all unique, all taken from the data
    CentroidInitializer init(3);
    Dataset c = init.initialize(data);
    std::set<std::vector<double>> unique(c.begin(), c.end());
    std::set<std::vector<double>> original(data.begin(), data.end());
    assert(c.size() == 3 && unique.size() == 3);
    for (const auto& p : c)
        assert(original.count(p) == 1);

    // k equal to the dataset size uses every point
    assert(CentroidInitializer(5).initialize(data).size() == 5);

    // getK / setK
    assert(init.getK() == 3);
    init.setK(2);
    assert(init.getK() == 2 && init.initialize(data).size() == 2);

    // Same seed gives the same result
    assert(CentroidInitializer(3, 42).initialize(data) ==
           CentroidInitializer(3, 42).initialize(data));

    std::cout << "All tests passed\n";
}