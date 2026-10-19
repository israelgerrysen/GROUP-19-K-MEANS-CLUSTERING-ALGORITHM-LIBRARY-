#pragma once

#include <vector>

/**
• @brief Detects and handles empty clusters in the K-Means algorithm
• by reassigning the furthest data point to the empty cluster.
• @param data The full dataset represented as a 2D vector of doubles.
• @param centroids The current cluster centroids as a 2D vector of doubles.
• @param assignments A vector containing the current cluster label for each data point.
*/
void handleEmptyClusters(
const std::vector<std::vector<double>>& data,
std::vector<std::vector<double>>& centroids,
std::vector<int>& assignments
);