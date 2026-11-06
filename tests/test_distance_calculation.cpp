#include "k_means/Distance_Calculation.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

int main() {
    using Point = DistanceCalculator::Point;
    auto near = [](double a, double b) { return std::abs(a - b) < 1e-9; };
    assert(near(DistanceCalculator::distance({0, 0}, {3, 4}), 5.0));
    assert(near(DistanceCalculator::squareddistance({0, 0}, {3, 4}), 25.0));
    assert(near(DistanceCalculator::distance({2}, {-3}), 5.0));
    assert(near(DistanceCalculator::distance({1, 2, 2}, {0, 0, 0}), 3.0));
    assert(near(DistanceCalculator::distance({}, {}), 0.0));
    assert(near(DistanceCalculator::distance(Point(10, 1.0), Point(10, 0.0)), std::sqrt(10.0)));

    auto throws = [](auto&& action) {
        try { action(); } catch (const std::invalid_argument&) { return true; }
        return false;
    };
    assert(throws([] { DistanceCalculator::distance({1, 2}, {1, 2, 3}); }));
    assert(throws([] { DistanceCalculator::squareddistance({std::numeric_limits<double>::infinity()}, {0}); }));
}
