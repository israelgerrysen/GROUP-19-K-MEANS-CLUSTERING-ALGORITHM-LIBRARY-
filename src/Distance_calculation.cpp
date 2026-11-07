// Implements validated Euclidean and squared Euclidean distance for feature vectors.
// The shared validator rejects mismatched dimensions and non-finite coordinates.
#include "k_means/Distance_Calculation.hpp"

#include <cmath>
#include <stdexcept>

namespace {
void validatePoints(const DistanceCalculator::Point& a, const DistanceCalculator::Point& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Points must have the same number of dimensions.");
    for (double value : a) if (!std::isfinite(value)) throw std::invalid_argument("Point coordinates must be finite.");
    for (double value : b) if (!std::isfinite(value)) throw std::invalid_argument("Point coordinates must be finite.");
}
}

double DistanceCalculator::distance(const Point& p1, const Point& p2) {
    return std::sqrt(squareddistance(p1, p2));
}

double DistanceCalculator::squareddistance(const Point& p1, const Point& p2) {
    validatePoints(p1, p2);
    double sum = 0.0;
    for (std::size_t i = 0; i < p1.size(); ++i) {
        const double difference = p1[i] - p2[i];
        sum += difference * difference;
    }
    return sum;
}
