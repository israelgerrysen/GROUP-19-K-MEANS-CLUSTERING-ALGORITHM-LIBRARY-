// Build: g++ -std=c++17 test_short.cpp Centroid_initialization.cpp -o test_short
#include "Centroid_initialization.hpp"
#include <cassert>
#include <iostream>
#include <set>

std::vector<std::vector<double>> initializeCentroids(const std::vector<std::vector<double>>& dataset, int k);
int main() {
    std::vector<std::vector<double>> data = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

    // Invalid input returns empty
    assert(initializeCentroids({}, 2).empty());
    assert(initializeCentroids(data, 0).empty());
    assert(initializeCentroids(data, 6).empty());

    // Valid input: k centroids, all unique, all taken from the data
    auto c = initializeCentroids(data, 3);
    std::set<std::vector<double>> unique(c.begin(), c.end());
    assert(c.size() == 3 && unique.size() == 3);
    for (const auto& p : c)
        assert(std::set<std::vector<double>>(data.begin(), data.end()).count(p) == 1);

    std::cout << "All tests passed\n";
}