// Implements matrix cleanup and missing-value imputation column by column.
// oneHotEncode appends one indicator feature per distinct category in sorted order.
#include "k_means/DataPreprocessor.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <unordered_map>
#include <set>

namespace {
// Validate the matrix shape and return its feature count. NaN is allowed here
// because the preprocessing methods below are designed to handle missing values.
std::size_t validateMatrix(const std::vector<std::vector<double>>& data) {
    if (data.empty()) return 0;
    const auto columns = data.front().size();
    for (const auto& row : data) {
        if (row.size() != columns) throw std::invalid_argument("All dataset rows must have the same number of columns.");
        for (double value : row) if (std::isinf(value)) throw std::invalid_argument("Dataset values must not be infinite.");
    }
    return columns;
}
}

void DataPreprocessor::dropColumn(std::vector<std::vector<double>>& dataset, int columnIndex) {
    const auto columns = validateMatrix(dataset);
    if (columnIndex < 0 || static_cast<std::size_t>(columnIndex) >= columns)
        throw std::out_of_range("Column index is outside the dataset.");
    for (auto& row : dataset) row.erase(row.begin() + columnIndex);
}

void DataPreprocessor::dropRowsWithMissingData(std::vector<std::vector<double>>& dataset) {
    validateMatrix(dataset);
    dataset.erase(std::remove_if(dataset.begin(), dataset.end(), [](const auto& row) {
        return std::any_of(row.begin(), row.end(), [](double value) { return std::isnan(value); });
    }), dataset.end());
}

void DataPreprocessor::fillMissingWithMean(std::vector<std::vector<double>>& dataset) {
    const auto columns = validateMatrix(dataset);
    // Impute feature-by-feature so each replacement uses only that feature's data.
    for (std::size_t col = 0; col < columns; ++col) {
        long double sum = 0.0L;
        std::size_t count = 0;
        for (const auto& row : dataset) if (!std::isnan(row[col])) { sum += row[col]; ++count; }
        if (count == 0) throw std::invalid_argument("Cannot impute a column containing only missing values.");
        const double mean = static_cast<double>(sum / count);
        for (auto& row : dataset) if (std::isnan(row[col])) row[col] = mean;
    }
}

void DataPreprocessor::fillMissingWithMedian(std::vector<std::vector<double>>& dataset) {
    const auto columns = validateMatrix(dataset);
    // Sorting makes the middle observed value(s) available for each feature.
    for (std::size_t col = 0; col < columns; ++col) {
        std::vector<double> values;
        for (const auto& row : dataset) if (!std::isnan(row[col])) values.push_back(row[col]);
        if (values.empty()) throw std::invalid_argument("Cannot impute a column containing only missing values.");
        std::sort(values.begin(), values.end());
        const auto middle = values.size() / 2;
        const double median = values.size() % 2 ? values[middle]
            : values[middle - 1] / 2.0 + values[middle] / 2.0;
        for (auto& row : dataset) if (std::isnan(row[col])) row[col] = median;
    }
}

void DataPreprocessor::fillMissingWithMode(std::vector<std::vector<double>>& dataset) {
    const auto columns = validateMatrix(dataset);
    // Count observed values per feature; the first value to reach the maximum wins ties.
    for (std::size_t col = 0; col < columns; ++col) {
        std::unordered_map<double, std::size_t> frequencies;
        double mode = 0.0;
        std::size_t maxFrequency = 0;
        for (const auto& row : dataset) if (!std::isnan(row[col])) {
            const auto frequency = ++frequencies[row[col]];
            if (frequency > maxFrequency) { maxFrequency = frequency; mode = row[col]; }
        }
        if (maxFrequency == 0) throw std::invalid_argument("Cannot impute a column containing only missing values.");
        for (auto& row : dataset) if (std::isnan(row[col])) row[col] = mode;
    }
}

void DataPreprocessor::oneHotEncode(std::vector<std::vector<double>>& dataset,
                                    const std::vector<std::string>& categoricalColumn) {
    const auto columns = validateMatrix(dataset);
    if (dataset.size() != categoricalColumn.size())
        throw std::invalid_argument("There must be one category value per dataset row.");
    std::set<std::string> categories(categoricalColumn.begin(), categoricalColumn.end());
    if (categories.empty()) return;
    // A sorted shared category order ensures each output column means the same category.
    for (auto& row : dataset) row.reserve(columns + categories.size());
    for (std::size_t row = 0; row < dataset.size(); ++row)
        for (const auto& category : categories)
            dataset[row].push_back(categoricalColumn[row] == category ? 1.0 : 0.0);
}
