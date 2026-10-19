#include "k_means/DataPreprocessor.hpp"
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>

// drop a specific column from the dataset
//usually used when a column is irrelevant or redundant
void DataPreprocessor::dropColumn(std::vector<std::vector<double>>& dataset, int columnIndex) {
    for (auto& row : dataset) {
        if (columnIndex >= 0 && columnIndex < row.size()) {
            row.erase(row.begin() + columnIndex);
        }
    }
}

// drop rows that contain any NaN values
//usually used when the dataset is small and we want to remove incomplete data
void DataPreprocessor::dropRowsWithMissingData(std::vector<std::vector<double>>& dataset) {
    for (auto it = dataset.begin(); it != dataset.end(); ) {
        bool hasNaN = false;
        for (double val : *it) {
            if (std::isnan(val)) {
                hasNaN = true;
                break;
            }
        }
        if (hasNaN) {
            it = dataset.erase(it);
        } else {
            ++it;
        }
    }
}

// fill missing values in the dataset with the mean of the respective column
//usually used when we assume that the missing data is random and the mean is a good representation of the data
void DataPreprocessor::fillMissingWithMean(std::vector<std::vector<double>>& dataset) {
    if (dataset.empty()) return;
    size_t numCols = dataset[0].size();
    
    for (size_t col = 0; col < numCols; ++col) {
        double sum = 0.0;
        int validCount = 0;
        for (size_t row = 0; row < dataset.size(); ++row) {
            if (!std::isnan(dataset[row][col])) {
                sum += dataset[row][col];
                validCount++;
            }
        }
        double mean = (validCount > 0) ? (sum / validCount) : 0.0;
        for (size_t row = 0; row < dataset.size(); ++row) {
            if (std::isnan(dataset[row][col])) {
                dataset[row][col] = mean;
            }
        }
    }
}

// fill missing values in the dataset with the median of the respective column
//usually used when we want to reduce the influence of outliers in the data
void DataPreprocessor::fillMissingWithMedian(std::vector<std::vector<double>>& dataset) {
    if (dataset.empty()) return;
    size_t numCols = dataset[0].size();
    
    for (size_t col = 0; col < numCols; ++col) {
        std::vector<double> validValues;
        for (size_t row = 0; row < dataset.size(); ++row) {
            if (!std::isnan(dataset[row][col])) {
                validValues.push_back(dataset[row][col]);
            }
        }
        if (validValues.empty()) continue; 
        
        std::sort(validValues.begin(), validValues.end());
        double median = 0.0;
        size_t size = validValues.size();
        
        if (size % 2 == 0) {
            median = (validValues[size / 2 - 1] + validValues[size / 2]) / 2.0;
        } else {
            median = validValues[size / 2];
        }
        
        for (size_t row = 0; row < dataset.size(); ++row) {
            if (std::isnan(dataset[row][col])) {
                dataset[row][col] = median;
            }
        }
    }
}

// fill missing values in the dataset with the mode of the respective column
//usually used when we want to replace missing values with the most common value in the data
void DataPreprocessor::fillMissingWithMode(std::vector<std::vector<double>>& dataset) {
    if (dataset.empty()) return;
    size_t numCols = dataset[0].size();
    
    for (size_t col = 0; col < numCols; ++col) {
        std::unordered_map<double, int> frequencies;
        int maxFreq = 0;
        double mode = 0.0;
        
        for (size_t row = 0; row < dataset.size(); ++row) {
            double val = dataset[row][col];
            if (!std::isnan(val)) {
                frequencies[val]++;
                if (frequencies[val] > maxFreq) {
                    maxFreq = frequencies[val];
                    mode = val;
                }
            }
        }
        if (maxFreq == 0) continue; 
        
        for (size_t row = 0; row < dataset.size(); ++row) {
            if (std::isnan(dataset[row][col])) {
                dataset[row][col] = mode;
            }
        }
    }
}

// puts the dataset into a binary format based on categorical strings
//usually used when we want to convert categorical data into a numerical format
void DataPreprocessor::oneHotEncode(std::vector<std::vector<double>>& dataset, const std::vector<std::string>& categoricalColumn) {
    if (dataset.size() != categoricalColumn.size()) return; 

    std::set<std::string> uniqueCategories(categoricalColumn.begin(), categoricalColumn.end());

    for (size_t row = 0; row < dataset.size(); ++row) {
        for (const auto& category : uniqueCategories) {
            if (categoricalColumn[row] == category) {
                dataset[row].push_back(1.0); 
            } else {
                dataset[row].push_back(0.0); 
            }
        }
    }
}