#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "k_means/DataPreprocessor.hpp"

void testDropColumn() {
    std::vector<std::vector<double>> data = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };
    
    // Drop the middle column (index 1)
    DataPreprocessor::dropColumn(data, 1);
    
    // Check that the column was actually removed
    assert(data[0].size() == 2);
    assert(data[0][0] == 1.0 && data[0][1] == 3.0);
    assert(data[1][0] == 4.0 && data[1][1] == 6.0);
    
    std::cout << "testDropColumn passed!\n";
}

void testDropRowsWithMissingData() {
    std::vector<std::vector<double>> data = {
        {1.0, 2.0},
        {3.0, std::nan("")}, // This row should be deleted
        {5.0, 6.0}
    };
    
    DataPreprocessor::dropRowsWithMissingData(data);
    
    // Check that only 2 rows remain, and the middle one is gone
    assert(data.size() == 2);
    assert(data[0][0] == 1.0);
    assert(data[1][0] == 5.0);
    
    std::cout << "testDropRowsWithMissingData passed!\n";
}

void testFillMissingWithMean() {
    std::vector<std::vector<double>> data = {
        {1.0, 10.0},
        {3.0, std::nan("")}, // Mean of column 1 (10 and 30) is 20
        {5.0, 30.0}
    };
    
    DataPreprocessor::fillMissingWithMean(data);
    
    // Check that the NaN value was replaced by 20.0
    assert(data.size() == 3);
    assert(data[1][1] == 20.0);
    
    std::cout << "testFillMissingWithMean passed!\n";
}

int main() {
    std::cout << "--- Running Preprocessor Tests ---\n";
    
    testDropColumn();
    testDropRowsWithMissingData();
    testFillMissingWithMean();
    
    std::cout << "All internal logic tests passed successfully!\n";
    return 0;
}