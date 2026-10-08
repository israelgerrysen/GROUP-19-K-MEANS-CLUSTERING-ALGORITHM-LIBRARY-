#ifndef DATAPREPROCESSOR_HPP
#define DATAPREPROCESSOR_HPP

#include <vector>
#include <string>

class DataPreprocessor {
public:
    static void dropColumn(std::vector<std::vector<double>>& dataset, int columnIndex);
    static void dropRowsWithMissingData(std::vector<std::vector<double>>& dataset);
    static void fillMissingWithMean(std::vector<std::vector<double>>& dataset);
    static void fillMissingWithMedian(std::vector<std::vector<double>>& dataset);
    static void fillMissingWithMode(std::vector<std::vector<double>>& dataset);
    
    // Appends binary columns to the dataset based on categorical strings
    static void oneHotEncode(std::vector<std::vector<double>>& dataset, const std::vector<std::string>& categoricalColumn);
};

#endif // DATAPREPROCESSOR_HPP