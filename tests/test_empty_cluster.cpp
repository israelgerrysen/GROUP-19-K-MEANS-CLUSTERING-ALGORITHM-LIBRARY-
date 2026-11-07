#include "k_means/EmptyCluster.hpp"

#include <cassert>
#include <stdexcept>
#include <vector>

int main() {
    using Dataset = std::vector<std::vector<double>>;
    Dataset data{{0, 0}, {1, 0}, {10, 0}, {11, 0}, {50, 0}};
    Dataset centroids{{0, 0}, {10, 0}, {25, 0}, {40, 0}};
    std::vector<int> labels{0, 0, 1, 1, 1}; // clusters 2 and 3 are empty
    handleEmptyClusters(data, centroids, labels);

    std::vector<int> counts(centroids.size(), 0);
    for (std::size_t i = 0; i < labels.size(); ++i) {
        ++counts[static_cast<std::size_t>(labels[i])];
        assert(centroids[static_cast<std::size_t>(labels[i])] == data[i] || labels[i] < 2);
    }
    assert(counts == std::vector<int>({1, 2, 1, 1}));
    assert(labels[4] == 2); // the farthest point enters the first empty cluster
    assert(centroids[2] == data[4]);
    std::size_t pointForFourthCluster = labels.size();
    for (std::size_t i = 0; i < labels.size(); ++i)
        if (labels[i] == 3) pointForFourthCluster = i;
    assert(pointForFourthCluster < labels.size() && pointForFourthCluster != 4);
    assert(centroids[3] == data[pointForFourthCluster]);

    auto throwsInvalidArgument = [](auto&& action) {
        try { action(); } catch (const std::invalid_argument&) { return true; }
        return false;
    };
    assert(throwsInvalidArgument([] {
        Dataset emptyData, oneCentroid{{0}};
        std::vector<int> noLabels;
        handleEmptyClusters(emptyData, oneCentroid, noLabels);
    }));
    assert(throwsInvalidArgument([&] {
        std::vector<int> tooFewLabels{0};
        handleEmptyClusters(data, centroids, tooFewLabels);
    }));
    assert(throwsInvalidArgument([&] {
        std::vector<int> invalidLabel{0, 0, 1, 1, 99};
        handleEmptyClusters(data, centroids, invalidLabel);
    }));
    assert(throwsInvalidArgument([] {
        Dataset twoPoints{{0}, {1}}, tooManyCentroids{{0}, {1}, {2}};
        std::vector<int> labels{0, 1};
        handleEmptyClusters(twoPoints, tooManyCentroids, labels);
    }));
    assert(throwsInvalidArgument([] {
        Dataset oneDimensional{{0}, {1}}, malformedCentroids{{0, 0}, {1}};
        std::vector<int> labels{0, 1};
        handleEmptyClusters(oneDimensional, malformedCentroids, labels);
    }));
}
