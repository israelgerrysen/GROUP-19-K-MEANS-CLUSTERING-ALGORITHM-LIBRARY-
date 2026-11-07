// API for repairing empty clusters after assignment by moving a far-away point
// from a cluster with multiple members and updating the corresponding label and centroid.
#pragma once

#include <vector>

// Reassigns farthest points from clusters containing multiple points to empty
// clusters, updating both centroids and labels. Throws invalid_argument when
// the inputs are inconsistent or an empty cluster cannot be repopulated.
void handleEmptyClusters(
const std::vector<std::vector<double>>& data,
std::vector<std::vector<double>>& centroids,
std::vector<int>& assignments
);
