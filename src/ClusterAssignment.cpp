// Implements the assignment half of a K-Means iteration by selecting the nearest centroid.
// Comparing squared distances preserves nearest-centroid ordering without square roots.
#include "k_means/ClusterAssignment.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

std::vector<int> ClusterAssignment::assignClusters(
    const Dataset& data, const Dataset& centroids) {
    if (data.empty()) throw std::invalid_argument("Data must not be empty.");
    if (centroids.empty()) throw std::invalid_argument("Centroids must not be empty.");
    const auto dimensions = data.front().size();
    if (dimensions == 0) throw std::invalid_argument("Points must contain at least one feature.");
    const auto validatePoint = [dimensions](const Point& point) {
        if (point.size() != dimensions) throw std::invalid_argument("All points must have the same dimension.");
        for (double value : point) if (!std::isfinite(value)) throw std::invalid_argument("Point coordinates must be finite.");
    };
    for (const auto& point : data) validatePoint(point);
    for (const auto& centroid : centroids) validatePoint(centroid);

    // Keep one result slot per point; reserve avoids repeated reallocations.
    std::vector<int> labels;
    labels.reserve(data.size());
    for (const auto& point : data) {
        // Start with centroid zero. Strict improvement keeps lowest-index ties.
        std::size_t best = 0;
        double bestDistance = DistanceCalculator::squareddistance(point, centroids.front());
        for (std::size_t c = 1; c < centroids.size(); ++c) {
            const double distance = DistanceCalculator::squareddistance(point, centroids[c]);
            if (distance < bestDistance) {
                bestDistance = distance;
                best = c;
            }
        }
        if (best > static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::overflow_error("Number of clusters exceeds label capacity.");
        labels.push_back(static_cast<int>(best));
    }
    return labels;
}
