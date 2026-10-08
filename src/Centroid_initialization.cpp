#include "Centroid_initialization.hpp"



#include <algorithm>
#include <numeric>
#include <random>

std::vector<std::vector<double>> initializeCentroids(const std::vector<std::vector<double>>& data, int k) {
    std::vector<std::vector<double>> centroids;
    if (data.empty() || k <= 0 || k > (int)data.size()) {
        return centroids;
    }

    // List every index 0..n-1, then shuffle them randomly
    std::vector<int> indices(data.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::mt19937 gen(std::random_device{}());
    std::shuffle(indices.begin(), indices.end(), gen);

    // The first k shuffled indices are k unique random points
    for (int i = 0; i < k; i++) {
        centroids.push_back(data[indices[i]]);
    }
    return centroids;
}