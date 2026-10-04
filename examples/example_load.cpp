#include <iostream>
#include "k_means/DataLoader.hpp"

int main() {
    try {
        // Call the static method directly using the class scope
        auto dataset = DataLoader::loadCSV("data/input/football.csv");
        
        std::cout << "---Dataset Preview ---\n";
        std::cout << "Successfully loaded " << dataset.size() << " rows.\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    
    return 0;
}