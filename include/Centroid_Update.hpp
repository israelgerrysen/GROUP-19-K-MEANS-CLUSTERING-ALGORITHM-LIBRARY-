// ============================================================================
// Centroid_Update.hpp
//
// Header file for the CentroidUpdater class.
//
// Role in K-Means:
//   K-Means repeats two steps until the clusters stop changing:
//     1. Assignment : give each point to its nearest centroid
//                     (done by ClusterAssignment).
//     2. Update     : move each centroid to the average of its points
//                     (done by this class, CentroidUpdater).
//   This file only DECLARES the class. The actual code is in
//   Centroid_Update.cpp.
// ============================================================================



#ifndef CENTROID_UPDATE_HPP
#define CENTROID_UPDATE_HPP
//#include "Distance_Calculation.hpp"

#include <vector>


// Moves every centroid to the mean (average) of the points assigned to it.
// All functions are static, so no object is needed:
//     CentroidUpdater::update(data, assignments, centroids);
class CentroidUpdater {
public:
    
// A Point is one data item: a list of numbers, one per feature
    // (dimension). Example: {1.5, 2.0} is a 2-D point.
using Point   = std::vector<double>;
    
    
    // A Dataset is a list of points. It is used for both the data and the
    // centroids, because a centroid is just a point.
    using Dataset = std::vector<Point>;


   // Returns the new centroids: centroid c becomes the mean of all points
    // whose assignment is c. The inputs are not changed.
    // A cluster with no points keeps its current centroid; fixing such empty
    // clusters is the job of EmptyClusterHandler.
    // Throws std::invalid_argument if data or currentCentroids are empty,
    // if assignments.size() != data.size(), if a label is outside
    // 0..currentCentroids.size()-1, or if point and centroid dimensions differ.
    //
    // Parameters:
    //   data             : all the data points (not changed)
    //   assignments      : assignments[i] is the cluster index of data[i]
    //                      (usually produced by ClusterAssignment)
    //   currentCentroids : the centroids from the previous step (not changed);
    //                      also decides how many clusters (k) there are
    // Returns: a new Dataset with the same number of centroids as
    //          currentCentroids.
    static Dataset update(const Dataset& data,
                          const std::vector<int>& assignments,
                          const Dataset& currentCentroids);

    // This is a utility class, so objects cannot be created.
    // "= delete" removes the default constructor, so writing
    //     CentroidUpdater u;
    // gives a compile error. The class is only used through its static
    // function.
    CentroidUpdater() = delete;
};

#endif // CENTROID_UPDATE_HPP

