// ============================================================================
// Centroid_Update.cpp
//
// Implementation of CentroidUpdater::update.
//
// Idea (the "update step" of K-Means):
//   For every cluster, add up all the points that belong to it, then divide
//   by how many points there are. That average is the cluster's new centroid.
//
// Example (1-D):
//   points {2, 4, 9}, assignments {0, 0, 1}
//   cluster 0 has points 2 and 4 -> new centroid = (2 + 4) / 2 = 3
//   cluster 1 has point  9       -> new centroid = 9 / 1       = 9
// ============================================================================

// The header with the class declaration (Point, Dataset, update).
#include "k_means/Centroid_Update.hpp"

// std::size_t: the unsigned type used for sizes and loop counters.
#include <cstddef>

// std::invalid_argument: the exception thrown when the input is not valid.
#include <stdexcept>

// "CentroidUpdater::Dataset" is written in front of the function name because
// the return type Dataset belongs to the class. Inside the parameter list the
// class scope is already active, so plain "Dataset" works there.
CentroidUpdater::Dataset CentroidUpdater::update(const Dataset& data,
                                                 const std::vector<int>& assignments,
                                                 const Dataset& currentCentroids)
{
   
   // ---------------------------------------------------------------
    // Step 1: Check the input before doing any work.
    // Stopping early with a clear message is safer than crashing or
    // returning wrong numbers later.
    // ---------------------------------------------------------------

   // With no data there is nothing to average.
    if (data.empty()) {
        throw std::invalid_argument("Data must not be empty.");
    }

    // With no centroids there are no clusters to update.
    if (currentCentroids.empty()) {
        throw std::invalid_argument("Centroids must not be empty.");
    }
    // Each data point needs exactly one cluster label.
    if (assignments.size() != data.size()) {
        throw std::invalid_argument("There must be one assignment per data point.");
    }
     // k = the number of clusters (one centroid per cluster).
    const std::size_t k = currentCentroids.size();

    // dimensions = how many numbers each point has. The first centroid is
    // used as the reference size.
    const std::size_t dimensions = currentCentroids.front().size();
    // Every other centroid must have the same number of dimensions.
    for (const auto& centroid : currentCentroids) {
        if (centroid.size() != dimensions) {
            throw std::invalid_argument("All centroids must have the same dimension.");
        }
    }

     // ---------------------------------------------------------------
    // Step 2: Add up the points of each cluster and count them.
    // ---------------------------------------------------------------

    // sums[c] will hold the running total of all points in cluster c.
    // It starts with k points of all zeros, each with `dimensions` numbers.
    Dataset sums(k, Point(dimensions, 0.0));
    // counts[c] will hold how many points are in cluster c (starts at 0).
    std::vector<int> counts(k, 0);

    
    // Look at every data point once.
    for (std::size_t i = 0; i < data.size(); ++i) {
        // The cluster number that point i belongs to.
        const int label = assignments[i];


        // The label must be a valid cluster index: 0 .. k-1.
        // (The cast to size_t is done after the "< 0" test, so a negative
        // number is caught first and not turned into a huge positive one.)
        if (label < 0 || static_cast<std::size_t>(label) >= k) {
            throw std::invalid_argument("Assignment label is outside the centroid range.");
        }
        // The point must have the same number of dimensions as the centroids.
        if (data[i].size() != dimensions) {
            throw std::invalid_argument("Point and centroid dimensions differ.");
        }

        // Convert the label to an unsigned index so it can be used safely
        // to access the vectors.
        const std::size_t cluster = static_cast<std::size_t>(label);


        // Add this point to its cluster's running total, one dimension at
        // a time (e.g. add all x values together, all y values together).
        for (std::size_t j = 0; j < dimensions; ++j) {
            sums[cluster][j] += data[i][j];
        }

        // One more point belongs to this cluster.
        ++counts[cluster];
    }

     // ---------------------------------------------------------------
    // Step 3: Turn the totals into averages.
    // ---------------------------------------------------------------

    // Start from a copy of the old centroids. This way, any cluster that
    // gets no points automatically keeps its old centroid, and the
    // original input is never changed.

    
    Dataset updated = currentCentroids;

    // New centroid = sum / count. An empty cluster keeps its old centroid.
    for (std::size_t c = 0; c < k; ++c) {
        // Only update clusters that have at least one point.
        // This also avoids dividing by zero.
        if (counts[c] > 0) {
            for (std::size_t j = 0; j < dimensions; ++j) {
                // The mean of dimension j = total of dimension j / number of points.
                updated[c][j] = sums[c][j] / counts[c];
            }
        }
    }

    // Give the new centroids back to the caller.
    return updated;
}
