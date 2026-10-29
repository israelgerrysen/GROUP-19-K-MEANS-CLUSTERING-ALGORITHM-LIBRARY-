#include "kmeans_example_utils.hpp"

#include <iostream>
#include <limits>
#include <exception>
#include <vector>

int main() {
    // Two clear groups, plus one missing feature to demonstrate imputation.
    const kmeans_example::Dataset data{
        {1.0, 1.0}, {1.2, 0.8}, {0.8, 1.1}, {1.1, 1.3},
        {8.0, 8.0}, {8.2, 7.8}, {7.8, 8.1}, {8.1, 8.3},
        {1.0, std::numeric_limits<double>::quiet_NaN()}
    };

    try {
        const auto result = kmeans_example::cluster(data, 2, 42);
        kmeans_example::printResult(result);
        std::cout << "Point cluster labels: ";
        for (std::size_t i = 0; i < result.labels.size(); ++i) {
            if (i != 0) std::cout << ' ';
            std::cout << result.labels[i];
        }
        std::cout << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Clustering failed: " << error.what() << '\n';
        return 1;
    }
}
