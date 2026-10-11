#include <vector>
#include "KMeans.h"
#include <cmath>
#include <algorithm>
#include <limits>

// Assuming data is std::vector<std::vector<double>> and centroids is same
void handleEmptyClusters(
const std::vector<std::vector<double>>& data,
std::vector<std::vector<double>>& centroids,
std::vector<int>& assignments) {

int k = centroids.size();
int dimensions = centroids[0].size();

// Count how many points are in each cluster
std::vector<int> counts(k, 0);
for (int label : assignments) {
counts[label]++;
}

// Check for any empty clusters
for (int i = 0; i < k; ++i) {
if (counts[i] == 0) {
// Find the point furthest from its current centroid
double max_distance = -1.0;
int farthest_point_idx = -1;

for (size_t p = 0; p < data.size(); ++p) {
int current_cluster = assignments[p];

// Calculate distance to current assigned centroid
double dist = 0.0;
for (int d = 0; d < dimensions; ++d) {
double diff = data[p][d] - centroids[current_cluster][d];
dist += diff * diff;
}

if (dist > max_distance) {
max_distance = dist;
farthest_point_idx = p;
}
}

// Reassign the farthest point to the empty cluster
if (farthest_point_idx != -1) {
assignments[farthest_point_idx] = i;
centroids[i] = data[farthest_point_idx]; // Set it as the new centroid
}
}
}
}