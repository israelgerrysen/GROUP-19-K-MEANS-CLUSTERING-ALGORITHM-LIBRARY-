#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <vector>
#include <string>

class DataLoader {
public:
    // Loads a CSV file and converts the data into a 2D vector of doubles
    static std::vector<std::vector<double>> loadCSV(const std::string& filename);
};

#endif // DATALOADER_HPP