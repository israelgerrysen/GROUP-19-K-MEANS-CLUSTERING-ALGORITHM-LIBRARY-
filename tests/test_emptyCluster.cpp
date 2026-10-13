#include <iostream>
#include <vector>
#include "k_means/EmptyCluster.hpp"

int main() {
// 1. Create a dummy dataset (5 points, 2 dimensions)
std::vector<std::vector<double>> data = {
{1.0, 1.0},
{1.5, 2.0},
{8.0, 8.0},
{8.5, 9.0},
{9.0, 8.5}
};

// 2. Define 3 centroids (K = 3)
// Notice we will intentionally create a situation where cluster 2 has 0 points initially.
std::vector<std::vector<double>> centroids = {
{1.2, 1.5}, // Centroid 0
{8.2, 8.5}, // Centroid 1
{5.0, 5.0} // Centroid 2 (This one will have no points assigned to it)
};

// 3. Set assignments where points only belong to cluster 0 and cluster 1.
// Cluster index 2 is completely empty.
std::vector<int> assignments = {0, 0, 1, 1, 1};

std::cout << "--- BEFORE EMPTY CLUSTER HANDLING ---\n";
for (size_t i = 0; i < centroids.size(); ++i) {
std::cout << "Centroid " << i << ": (" << centroids[i][0] << ", " << centroids[i][1] << ")\n";
}

// 4. Run your function
handleEmptyClusters(data, centroids, assignments);

std::cout << "\n--- AFTER EMPTY CLUSTER HANDLING ---\n";
for (size_t i = 0; i < centroids.size(); ++i) {
std::cout << "Centroid " << i << ": (" << centroids[i][0] << ", " << centroids[i][1] << ")\n";
}

// Print final assignments to see which point was moved to cluster 2
std::cout << "\nFinal Point Assignments:\n";
for (size_t p = 0; p < assignments.size(); ++p) {
std::cout << "Point " << p << " -> Cluster " << assignments[p] << "\n";
}

return 0;
}