// Implements seeded or random selection of distinct data rows for initial centroids.
// Input validation ensures every selected point has the same finite feature vector shape.
#include "k_means/Centroid_initialization.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>


CentroidInitializer::CentroidInitializer(int k) : k_(k), gen_(std::random_device{}()) {
    if (k < 1) throw std::invalid_argument("k must be at least 1.");
}

CentroidInitializer::CentroidInitializer(int k, unsigned int seed) : k_(k), gen_(seed) {
    if (k < 1) throw std::invalid_argument("k must be at least 1.");
}

int CentroidInitializer::getK() const {
    return k_;
}

void CentroidInitializer::setK(int k) {
    if (k < 1) throw std::invalid_argument("k must be at least 1.");
    k_ = k;
}

CentroidInitializer::Dataset CentroidInitializer::initialize(const Dataset& data) {
    Dataset centroids;
    if (data.empty()) throw std::invalid_argument("Data must not be empty.");
    if (static_cast<std::size_t>(k_) > data.size()) throw std::invalid_argument("k cannot exceed the number of data points.");
    const auto dimensions = data.front().size();
    if (dimensions == 0) throw std::invalid_argument("Points must contain at least one feature.");
    for (const auto& point : data) {
        if (point.size() != dimensions) throw std::invalid_argument("All data points must have the same dimension.");
        for (double value : point) if (!std::isfinite(value)) throw std::invalid_argument("Data values must be finite.");
    }

    // List every index 0..n-1, then shuffle them randomly
    std::vector<int> indices(data.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), gen_);

    // The first k shuffled indices are k unique random points
    for (int i = 0; i < k_; i++) {
        centroids.push_back(data[indices[i]]);
    }
    return centroids;
}
