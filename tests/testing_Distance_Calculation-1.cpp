// Build: g++ -std=c++17 testing_distance.cpp Distance_calculation1.cpp -o testing_distance
#include "Distance_Calculation.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

static int failed = 0;

static void check(const char* name, bool ok) {
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << "\n";
    if (!ok) ++failed;
}

static bool near(double a, double b) { return std::fabs(a - b) < 1e-9; }

int main() {
    using V = std::vector<double>;

    check("3-4-5 triangle gives 5",
          near(DistanceCalculator::distance({0, 0}, {3, 4}), 5.0));

    check("identical points give 0",
          near(DistanceCalculator::distance({1.5, -2, 7}, {1.5, -2, 7}), 0.0));

    check("1D distance is the absolute difference",
          near(DistanceCalculator::distance({2}, {-3}), 5.0));

    check("negative coordinates",
          near(DistanceCalculator::distance({-1, -1}, {2, 3}), 5.0));

    check("3D point: (1,2,2) to origin is 3",
          near(DistanceCalculator::distance({1, 2, 2}, {0, 0, 0}), 3.0));

    check("symmetric: d(a,b) == d(b,a)",
          near(DistanceCalculator::distance({1, 5, 9}, {4, 1, 2}),
               DistanceCalculator::distance({4, 1, 2}, {1, 5, 9})));

    check("10 dimensions: ones vs zeros gives sqrt(10)",
          near(DistanceCalculator::distance(V(10, 1.0), V(10, 0.0)), std::sqrt(10.0)));

    check("empty points give 0",
          near(DistanceCalculator::distance({}, {}), 0.0));

    bool threw = false;
    try { DistanceCalculator::distance({1, 2}, {1, 2, 3}); }
    catch (const std::invalid_argument&) { threw = true; }
    check("different dimensions throw invalid_argument", threw);

    std::cout << (failed == 0 ? "\nAll tests passed\n" : "\nSome tests FAILED\n");
    return failed == 0 ? 0 : 1;
}