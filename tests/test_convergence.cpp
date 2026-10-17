#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include "k_means/ConvergenceDetector.hpp"

using Centroids = std::vector<std::vector<double>>;

static int g_failures = 0;

void expect(bool condition, const std::string& message) {
    std::cout << (condition ? "[PASS] " : "[FAIL] ") << message << "\n";
    if (!condition) {
        ++g_failures;
    }
}

template <typename F>
bool throwsInvalidArgument(F f) {
    try {
        f();
    } catch (const std::invalid_argument&) {
        return true;
    }
    return false;
}

int main() {
    std::cout << "===== ConvergenceDetector unit tests =====\n\n";

    {
        ConvergenceDetector detector(0.01);
        Centroids oldC = {{1.0, 1.0}, {5.0, 5.0}};
        Centroids newC = {{1.005, 1.002},   // moved ~0.0054
                          {5.001, 5.003}};  // moved ~0.0032

        expect(detector.centroidsConverged(oldC, newC),
               "centroidsConverged returns true when movement is below tolerance");
    }

    {
        ConvergenceDetector detector(0.01);
        Centroids oldC = {{1.0, 1.0}, {5.0, 5.0}};
        Centroids newC = {{1.5, 1.0}, {5.0, 5.0}};

        expect(!detector.centroidsConverged(oldC, newC),
               "centroidsConverged returns false when movement exceeds tolerance");
    }

    {
        ConvergenceDetector detector;
        std::vector<int> a1 = {0, 1, 0, 1, 0};
        std::vector<int> a2 = {0, 1, 0, 1, 0};

        expect(detector.assignmentsConverged(a1, a2),
               "assignmentsConverged returns true for identical labels");
    }

    {
        ConvergenceDetector detector;
        std::vector<int> a1 = {0, 1, 0, 1, 0};
        std::vector<int> a2 = {0, 1, 1, 1, 0};

        expect(!detector.assignmentsConverged(a1, a2),
               "assignmentsConverged returns false when any label changes");
    }

    // Not converged on purpose, so only the iteration count can decide.
    {
        ConvergenceDetector detector(1e-4, 5);
        Centroids oldC = {{0.0, 0.0}};
        Centroids newC = {{9.0, 9.0}};
        std::vector<int> oldA = {0, 1};
        std::vector<int> newA = {1, 0};

        expect(!detector.shouldStop(oldC, newC, oldA, newA, 4),
               "shouldStop returns false when not converged and under the limit");
        expect(detector.shouldStop(oldC, newC, oldA, newA, 5),
               "shouldStop returns true at the iteration limit even if not converged");
        expect(detector.shouldStop(oldC, newC, oldA, newA, 6),
               "shouldStop returns true past the iteration limit");
    }

    {
        ConvergenceDetector detector(0.01, 100);
        Centroids oldC = {{2.0, 3.0}};
        Centroids nearC = {{2.001, 3.001}};
        Centroids farC = {{8.0, 9.0}};
        std::vector<int> same = {0, 0, 1};
        std::vector<int> diff = {0, 1, 1};

        expect(detector.shouldStop(oldC, nearC, same, diff, 10),
               "shouldStop returns true when only the centroids have stabilised");
        expect(detector.shouldStop(oldC, farC, same, same, 10),
               "shouldStop returns true when only the assignments have stabilised");
        expect(!detector.shouldStop(oldC, farC, same, diff, 10),
               "shouldStop returns false when neither has stabilised");
    }

    {
        ConvergenceDetector detector(1e-5, 50);
        expect(std::abs(detector.getTolerance() - 1e-5) < 1e-12,
               "getTolerance returns the value set in constructor");
        expect(detector.getMaxIterations() == 50,
               "getMaxIterations returns the value set in constructor");

        detector.setTolerance(0.05);
        detector.setMaxIterations(200);
        expect(std::abs(detector.getTolerance() - 0.05) < 1e-12,
               "setTolerance updates the tolerance");
        expect(detector.getMaxIterations() == 200,
               "setMaxIterations updates the limit");
    }

    // 0.5 and 1.5 are exact in binary, so there is no rounding noise.
    {
        ConvergenceDetector detector(0.5);
        expect(detector.centroidsConverged(Centroids{{1.0, 0.0}}, Centroids{{1.5, 0.0}}),
               "centroidsConverged treats movement == tolerance as converged");
    }

    {
        ConvergenceDetector detector(0.01);
        const double nan = std::numeric_limits<double>::quiet_NaN();

        expect(detector.centroidsConverged(Centroids{}, Centroids{}),
               "centroidsConverged returns true for two empty centroid lists");

        expect(!detector.centroidsConverged(Centroids{{1.0}}, Centroids{{1.0}, {2.0}}),
               "centroidsConverged returns false when the number of centroids differs");

        expect(throwsInvalidArgument([&] {
                   detector.centroidsConverged(Centroids{{1.0, 2.0}}, Centroids{{1.0, 2.0, 3.0}});
               }),
               "centroidsConverged throws when centroid dimensions differ");

        // The other centroid has not moved, so only the NaN can make this false.
        expect(!detector.centroidsConverged(Centroids{{1.0, 1.0}, {5.0, 5.0}},
                                            Centroids{{nan, nan}, {5.0, 5.0}}),
               "centroidsConverged returns false when a centroid becomes NaN");

        expect(throwsInvalidArgument([&] {
                   detector.centroidsConverged(Centroids{{nan}, {1.0, 2.0}}, Centroids{{1.0}, {1.0, 2.0, 3.0}});
               }),
               "centroidsConverged still throws on a dimension mismatch that follows a NaN centroid");

        expect(!detector.assignmentsConverged(std::vector<int>{0, 1}, std::vector<int>{0, 1, 0}),
               "assignmentsConverged returns false when the label vectors differ in length");
    }

    {
        const double nan = std::numeric_limits<double>::quiet_NaN();
        const double inf = std::numeric_limits<double>::infinity();

        expect(throwsInvalidArgument([] { ConvergenceDetector d(-0.1); }),
               "constructor rejects a negative tolerance");
        expect(throwsInvalidArgument([&] { ConvergenceDetector d(nan); }),
               "constructor rejects a NaN tolerance");
        expect(throwsInvalidArgument([&] { ConvergenceDetector d(inf); }),
               "constructor rejects an infinite tolerance");
        expect(throwsInvalidArgument([] { ConvergenceDetector d(1e-4, 0); }),
               "constructor rejects maxIterations < 1");

        ConvergenceDetector detector(0.01, 10);
        expect(throwsInvalidArgument([&] { detector.setTolerance(-1.0); }),
               "setTolerance rejects a negative value");
        expect(throwsInvalidArgument([&] { detector.setMaxIterations(0); }),
               "setMaxIterations rejects zero");
        expect(std::abs(detector.getTolerance() - 0.01) < 1e-12 &&
               detector.getMaxIterations() == 10,
               "rejected setter calls leave the detector unchanged");
    }

    std::cout << "\n===== All tests finished: " << g_failures << " failure(s) =====\n";
    return g_failures == 0 ? 0 : 1;
}
