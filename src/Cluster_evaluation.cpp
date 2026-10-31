// Implements inertia: sum the squared distance from each point to its labeled centroid.
// Input checks protect label indexing and require finite, dimensionally consistent data.
#include "k_means/Cluster_Evaluator.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

double ClusterEvaluator::computeInertia(const Dataset& points,
                                        const std::vector<int>& labels,
                                        const Dataset& centroids) {
    if (points.empty()) throw std::invalid_argument("Points must not be empty.");
    if (centroids.empty()) throw std::invalid_argument("Centroids must not be empty.");
    if (labels.size() != points.size()) throw std::invalid_argument("There must be one label per point.");
    const auto dimensions = points.front().size();
    if (dimensions == 0) throw std::invalid_argument("Points must contain at least one feature.");
    const auto validatePoint = [dimensions](const Point& point) {
        if (point.size() != dimensions) throw std::invalid_argument("All points and centroids must have the same dimension.");
        for (double value : point) if (!std::isfinite(value)) throw std::invalid_argument("Point coordinates must be finite.");
    };
    for (const auto& point : points) validatePoint(point);
    for (const auto& centroid : centroids) validatePoint(centroid);

    // Accumulate in wider precision, then check that the result fits in double.
    long double inertia = 0.0L;
    for (std::size_t i = 0; i < points.size(); ++i) {
        const int label = labels[i];
        if (label < 0 || static_cast<std::size_t>(label) >= centroids.size())
            throw std::invalid_argument("Assignment label is outside the centroid range.");
        for (std::size_t d = 0; d < dimensions; ++d) {
            const long double delta = static_cast<long double>(points[i][d]) - centroids[static_cast<std::size_t>(label)][d];
            inertia += delta * delta;
        }
    }
    if (!std::isfinite(inertia) || inertia > std::numeric_limits<double>::max())
        throw std::overflow_error("Inertia exceeds double precision range.");
    return static_cast<double>(inertia);
}
