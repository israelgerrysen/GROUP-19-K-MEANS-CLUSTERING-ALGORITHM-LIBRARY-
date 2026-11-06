// API for reading numeric features from a header-based CSV file into a row-major matrix.
// Invalid or non-numeric cells are represented as NaN so preprocessing can handle them.
#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <cstddef>
#include <vector>
#include <string>

class DataLoader {
public:
    // Loads a CSV file and converts the data into a 2D vector of doubles
    // The first row is a header. Non-numeric cells become NaN for later
    // preprocessing. Optional zero-based column indexes select/reorder fields.
    static std::vector<std::vector<double>> loadCSV(
        const std::string& filename,
        const std::vector<std::size_t>& selectedColumns = {});
};

#endif // DATALOADER_HPP
