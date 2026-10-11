#pragma once
#include <vector>
#include <limits>
#include <cmath>

namespace k_means {

class ClusterAssignment {
public:
    static double calculateDistance(const std::vector<double>& point1, const std::vector<double>& point2) {
        double sum = 0.0;
        for (size_t i = 0; i < point1.size(); ++i) {
            sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
        }
        return std::sqrt(sum);
    }

    // TASK 6: Assigns each data point to the nearest centroid
    static std::vector<int> assignClusters(
        const std::vector<std::vector<double>>& data,
        const std::vector<std::vector<double>>& centroids)
    {
        std::vector<int> assignments(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            double minDistance = std::numeric_limits<double>::max();
            int bestCluster = 0;
            for (size_t j = 0; j < centroids.size(); ++j) {
                double distance = calculateDistance(data[i], centroids[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestCluster = static_cast<int>(j);
                }
            }
            assignments[i] = bestCluster;
        }
        return assignments;
    }
};

}