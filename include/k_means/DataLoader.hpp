#ifndef DATALOADER_HPP
#define DATALOADER_HPP

using namespace std;
#include <vector>
#include <string>

class DataLoader {
public:
    // Loads a CSV file and converts the data into a 2D vector of doubles
    static vector<vector<double>> loadCSV(const string& filename);
};

#endif // DATALOADER_HPP