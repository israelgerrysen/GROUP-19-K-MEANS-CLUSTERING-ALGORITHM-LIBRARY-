#ifndef DISTANCE_H
#define DISTANCE_H
#include <vector>

//Calculating the Euclidean distance between two n-dimensional points that are represented as vectors
//Calculates distances between two n-dimensional points.
// All functions are static, so no object is needed:
//     DistanceCalculator::euclidean(a, b);
class DistanceCalculator {
public:
    using Point = std::vector<double>;   // a point is a vector of feature values
 
    // Euclidean distance: sqrt of the sum of squared differences.
    // Throws std::invalid_argument if the points have different dimensions.
    static double distance(const Point& p1, const Point& p2);
 
    // Squared Euclidean distance (no square root). Faster, and enough when
    // you only need to compare distances, e.g. finding the nearest centroid.
    // Throws std::invalid_argument if the points have different dimensions.
    static double squareddistance(const Point& p1, const Point& p2);
 
    // This is a utility class, so objects cannot be created.
    DistanceCalculator() = delete;
};
 
#endif // DISTANCE_CALCULATION_HPP