#ifndef INITIALIZE_CENTROID
#define INITIALIZE_CENTROID
#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>


//initializeCentroids function declaration: initializes k centroids by randomly selecting existing data points)
std::vector<std::vector<double>> initializeCentroids(const std::vector<std::vector<double>>& dataset, int k);
#endif// INITIALIZATION_HPP
