#include "k_means/DataLoader.hpp"
#include "kmeans_example_utils.hpp"

#include <exception>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    // In football.csv, columns 12 and 13 are home and away goal counts.
    // Pass a different CSV path as the first command-line argument if needed.
    std::string filename = argc > 1 ? argv[1] : "data/input/football.csv";
    if (argc == 1 && !std::filesystem::exists(filename)) {
        for (const auto& candidate : std::vector<std::string>{
                 "../data/input/football.csv", "../../data/input/football.csv"}) {
            if (std::filesystem::exists(candidate)) {
                filename = candidate;
                break;
            }
        }
    }

    try {
        const auto data = DataLoader::loadCSV(filename, {12, 13});
        if (data.empty()) {
            std::cerr << "The selected CSV columns contain no data rows.\n";
            return 1;
        }

        const auto result = kmeans_example::cluster(data, 3, 42);
        std::cout << "Loaded " << data.size()
                  << " matches using home and away goals from " << filename << ".\n";
        kmeans_example::printResult(result);

        std::vector<std::size_t> counts(result.centroids.size(), 0);
        for (const int label : result.labels) ++counts[static_cast<std::size_t>(label)];
        for (std::size_t cluster = 0; cluster < counts.size(); ++cluster)
            std::cout << "Matches in cluster " << cluster << ": " << counts[cluster] << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Could not cluster CSV data: " << error.what() << '\n';
        return 1;
    }
}
