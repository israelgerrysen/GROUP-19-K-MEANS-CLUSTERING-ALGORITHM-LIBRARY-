// Implements convergence checks using centroid movement, unchanged labels, and an iteration cap.
// Tolerance and iteration settings are validated when constructed or changed.
#include "k_means/ConvergenceDetector.hpp"
#include <cmath>
#include <cstddef>
#include <stdexcept>

ConvergenceDetector::ConvergenceDetector(double tolerance, int maxIterations)
    : tolerance_(0.0), maxIterations_(1)
{
    setTolerance(tolerance);
    setMaxIterations(maxIterations);
}

void ConvergenceDetector::setTolerance(double t)
{
    if (!std::isfinite(t) || t < 0.0) {
        throw std::invalid_argument("ConvergenceDetector: tolerance must be finite and non-negative");
    }
    tolerance_ = t;
}

void ConvergenceDetector::setMaxIterations(int m)
{
    if (m < 1) {
        throw std::invalid_argument("ConvergenceDetector: maxIterations must be at least 1");
    }
    maxIterations_ = m;
}

double ConvergenceDetector::euclideanDistance(
    const std::vector<double>& a,
    const std::vector<double>& b)
{
    if (a.size() != b.size()) {
        throw std::invalid_argument("euclideanDistance: vectors must have the same dimension");
    }
    double sum = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        const double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

bool ConvergenceDetector::centroidsConverged(
    const std::vector<std::vector<double>>& oldCentroids,
    const std::vector<std::vector<double>>& newCentroids) const
{
    if (oldCentroids.size() != newCentroids.size()) {
        return false;
    }

    // Every pair is measured (no early exit) so a dimension mismatch always throws.
    bool converged = true;
    for (std::size_t i = 0; i < oldCentroids.size(); ++i) {
        // Written as !(<=) so that a NaN distance counts as not converged.
        if (!(euclideanDistance(oldCentroids[i], newCentroids[i]) <= tolerance_)) {
            converged = false;
        }
    }
    return converged;
}

bool ConvergenceDetector::assignmentsConverged(
    const std::vector<int>& oldAssignments,
    const std::vector<int>& newAssignments) const
{
    return oldAssignments == newAssignments;
}

bool ConvergenceDetector::shouldStop(
    const std::vector<std::vector<double>>& oldCentroids,
    const std::vector<std::vector<double>>& newCentroids,
    const std::vector<int>& oldAssignments,
    const std::vector<int>& newAssignments,
    int currentIteration) const
{
    if (currentIteration >= maxIterations_) {
        return true;
    }
    return centroidsConverged(oldCentroids, newCentroids)
        || assignmentsConverged(oldAssignments, newAssignments);
}
