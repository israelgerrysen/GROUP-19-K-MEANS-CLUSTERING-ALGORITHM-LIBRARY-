#include "k_means/DataLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

vector<vector<double>> DataLoader::loadCSV(const string& filename) {
    vector<vector<double>> dataset;
    ifstream myFile(filename);

    // Error handling if the file is missing or locked
    if (!myFile.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    string line;
    
    // ignore the first line of the CSV file (header)
    getline(myFile, line);

    // Read the file row by row
    while (getline(myFile, line)) {
        vector<double> row;
        string cell = "";
        bool inQuotes = false;
        
        // Parse character-by-character to respect quotation marks
        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            
            if (c == '"') {
                inQuotes = !inQuotes; // Toggle quote state
            } else if (c == ',' && !inQuotes) {
                // End of a cell reached outside of quotes
                try {
                    row.push_back(stod(cell));
                } catch (const invalid_argument& e) {
                    row.push_back(nan(""));
                } catch (const out_of_range& e) {
                    row.push_back(nan(""));
                }
                cell.clear();
            } else {
                cell += c;
            }
        }
        
        // Process the final cell in the row
        try {
            row.push_back(stod(cell));
        } catch (const invalid_argument& e) {
            row.push_back(nan(""));
        } catch (const out_of_range& e) {
            row.push_back(nan(""));
        }
        
        // Only add the row if it contains valid numerical data
        if (!row.empty()) {
            dataset.push_back(row);
        }
    }
    return dataset;
}