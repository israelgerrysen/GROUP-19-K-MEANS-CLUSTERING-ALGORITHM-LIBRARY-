// Repairs empty clusters by transferring the farthest eligible point from a donor cluster.
// Donor clusters retain at least one point; labels, counts, and the new centroid stay consistent.
#include "k_means/EmptyCluster.hpp"

#include <cmath>
#include <stdexcept>

void handleEmptyClusters(const std::vector<std::vector<double>>& data,
                         std::vector<std::vector<double>>& centroids,
                         std::vector<int>& assignments) {
    if (data.empty() || centroids.empty()) throw std::invalid_argument("Data and centroids must not be empty.");
    if (assignments.size() != data.size()) throw std::invalid_argument("There must be one assignment per data point.");
    if (centroids.size() > data.size()) throw std::invalid_argument("The number of clusters cannot exceed the number of data points.");
    const auto dimensions = data.front().size();
    if (dimensions == 0) throw std::invalid_argument("Points must contain at least one feature.");
    const auto validatePoint = [dimensions](const std::vector<double>& point) {
        if (point.size() != dimensions) throw std::invalid_argument("All points and centroids must have the same dimension.");
        for (double value : point) if (!std::isfinite(value)) throw std::invalid_argument("Point coordinates must be finite.");
    };
    for (const auto& point : data) validatePoint(point);
    for (const auto& centroid : centroids) validatePoint(centroid);

    std::vector<std::size_t> counts(centroids.size(), 0);
    for (int label : assignments) {
        if (label < 0 || static_cast<std::size_t>(label) >= centroids.size())
            throw std::invalid_argument("Assignment label is outside the centroid range.");
        ++counts[static_cast<std::size_t>(label)];
    }

    std::vector<bool> moved(data.size(), false);
    for (std::size_t empty = 0; empty < counts.size(); ++empty) {
        if (counts[empty] != 0) continue;
        std::size_t farthest = data.size();
        double farthestDistance = -1.0;
        for (std::size_t point = 0; point < data.size(); ++point) {
            const auto donor = static_cast<std::size_t>(assignments[point]);
            if (moved[point] || counts[donor] <= 1) continue;
            double squaredDistance = 0.0;
            for (std::size_t d = 0; d < dimensions; ++d) {
                const double delta = data[point][d] - centroids[donor][d];
                squaredDistance += delta * delta;
            }
            if (squaredDistance > farthestDistance) {
                farthestDistance = squaredDistance;
                farthest = point;
            }
        }
        if (farthest == data.size())
            throw std::invalid_argument("Cannot repopulate an empty cluster without emptying another cluster.");
        const auto donor = static_cast<std::size_t>(assignments[farthest]);
        --counts[donor];
        ++counts[empty];
        assignments[farthest] = static_cast<int>(empty);
        centroids[empty] = data[farthest];
        moved[farthest] = true;
    }
}
