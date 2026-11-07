// API for deciding whether K-Means has stabilized or reached its iteration limit.
// Callers can check centroid movement, assignment stability, or either stopping condition.
#ifndef CONVERGENCEDETECTOR_HPP
#define CONVERGENCEDETECTOR_HPP

#include <vector>

// Decides when K-Means should stop: centroids settled, assignments stable,
// or the iteration budget used up.
class ConvergenceDetector {
public:
    // tolerance must be finite and >= 0, maxIterations must be >= 1.
    // Throws std::invalid_argument otherwise (the setters do the same).
    explicit ConvergenceDetector(double tolerance = 1e-4, int maxIterations = 300);

    // True if no centroid moved more than the tolerance. False for a different
    // centroid count or non-finite coordinates.
    // Throws std::invalid_argument if the dimensions differ.
    bool centroidsConverged(
        const std::vector<std::vector<double>>& oldCentroids,
        const std::vector<std::vector<double>>& newCentroids) const;

    bool assignmentsConverged(
        const std::vector<int>& oldAssignments,
        const std::vector<int>& newAssignments) const;

    // True if centroids or assignments are stable, or currentIteration >=
    // maxIterations (so the caller decides if its counter starts at 0 or 1).
    bool shouldStop(
        const std::vector<std::vector<double>>& oldCentroids,
        const std::vector<std::vector<double>>& newCentroids,
        const std::vector<int>& oldAssignments,
        const std::vector<int>& newAssignments,
        int currentIteration) const;

    double getTolerance() const { return tolerance_; }
    int    getMaxIterations() const { return maxIterations_; }

    void setTolerance(double t);
    void setMaxIterations(int m);

private:
    double tolerance_;
    int    maxIterations_;

    static double euclideanDistance(
        const std::vector<double>& a,
        const std::vector<double>& b);
};

#endif
