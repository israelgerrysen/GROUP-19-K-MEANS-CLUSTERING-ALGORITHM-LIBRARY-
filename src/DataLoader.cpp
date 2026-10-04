#include "k_means/DataLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::vector<std::vector<double>> DataLoader::loadCSV(const std::string& filename) {
    std::vector<std::vector<double>> dataset;
    std::ifstream myFile(filename);

    // Error handling if the file is missing or locked
    if (!myFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line, cell;
    
    // Read the file row by row
    while (std::getline(myFile, line)) {
        std::vector<double> row;
        std::stringstream ss(line);

        // Split each row by commas
        while (std::getline(ss, cell, ',')) {
            try {
                // Convert the string to a double for K-Means distance math
                row.push_back(std::stod(cell));
            } catch (const std::invalid_argument& e) {
                // Skips headers or non-numeric text gracefully
                continue; 
            }
        }
        
        // Only add the row if it contains valid numerical data
        if (!row.empty()) {
            dataset.push_back(row);
        }
    }
    return dataset;
}