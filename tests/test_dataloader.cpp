#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <fstream>
#include "k_means/DataLoader.hpp"

using namespace std;

void createDummyCSV() {
    ofstream out("dummy_test.csv");
    out << "Header1,Header2,Header3\n";
    out << "1.5,2.5,3.5\n";
    out << "4.0,\"3,83\",6.0\n"; // Quoted field with an internal comma
    out << "7.0,,9.0\n";        // Empty cell
    out.close();
}

int main() {
    createDummyCSV();
    
    cout << "--- Running DataLoader Tests ---\n";
    
    auto dataset = DataLoader::loadCSV("dummy_test.csv");
    
    // 1. Verify Row Count
    assert(dataset.size() == 3);
    cout << "Row count test passed!\n";
    
    // 2. Verify Column Count (Ensures even widths despite missing data)
    assert(dataset[0].size() == 3);
    assert(dataset[1].size() == 3);
    assert(dataset[2].size() == 3);
    cout << "Column count test passed!\n";
    
    // 3. Verify Quoted Fields and Empty Cells
    // If the comma in "3,83" caused a split, the column widths above would fail
    assert(isnan(dataset[2][1])); 
    cout << "Quoted field and empty cell test passed!\n";
    
    cout << "All DataLoader logic tests passed successfully!\n";
    
    remove("dummy_test.csv");
    
    return 0;
}