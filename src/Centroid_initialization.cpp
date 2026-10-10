#include "Centroid_initialization.hpp"



CentroidInitializer::CentroidInitializer(int k) : k_(k), gen_(std::random_device{}()) {}

CentroidInitializer::CentroidInitializer(int k, unsigned int seed) : k_(k), gen_(seed) {}

int CentroidInitializer::getK() const {
    return k_;
}

void CentroidInitializer::setK(int k) {
    k_ = k;
}

CentroidInitializer::Dataset CentroidInitializer::initialize(const Dataset& data) {
    Dataset centroids;
    if (data.empty() || k_ <= 0 || k_ > (int)data.size()) {
        return centroids;
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