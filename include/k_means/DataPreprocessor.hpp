// API for cleaning a numeric matrix by removing columns/rows, imputing missing values,
// and appending one-hot columns for a separately supplied categorical feature.
#ifndef DATAPREPROCESSOR_HPP
#define DATAPREPROCESSOR_HPP

#include <vector>
#include <string>

class DataPreprocessor {
public:
    // Remove one feature from every row; columnIndex is zero-based.
    static void dropColumn(std::vector<std::vector<double>>& dataset, int columnIndex);
    // Delete every row containing NaN. These operations modify dataset in place.
    static void dropRowsWithMissingData(std::vector<std::vector<double>>& dataset);
    // Replace NaN values in each column using that column's observed values.
    // Each method throws if a column has no values from which to calculate a replacement.
    static void fillMissingWithMean(std::vector<std::vector<double>>& dataset);
    static void fillMissingWithMedian(std::vector<std::vector<double>>& dataset);
    static void fillMissingWithMode(std::vector<std::vector<double>>& dataset);
    
    // Append one 0/1 feature per distinct category, in sorted category order.
    // categoricalColumn must contain exactly one value for each dataset row.
    static void oneHotEncode(std::vector<std::vector<double>>& dataset, const std::vector<std::string>& categoricalColumn);
};

#endif // DATAPREPROCESSOR_HPP
