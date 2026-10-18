#include <iostream>
#include <vector>
#include <iomanip>
#include “InertiaEvaluator.hpp” 

Int main() {
    Std::cout << std::fixed << std::setprecision(4);

    // Sample dataset
    Std::vector<Point> dataset = {
        {1.0, 1.0}, {1.5, 2.0}, {2.0, 1.5},
        {8.0, 8.0}, {8.5, 9.0}, {9.0, 8.5}
    };

    // Cluster centroids
    Std::vector<Point> centroids = {
        {1.5, 1.5}, 
        {8.5, 8.5}  
    };

    // Mock labels assigning points to clusters 0 and 1
    Std::vector<int> labels = {0, 0, 0, 1, 1, 1};

    // Calculate inertia using the function from your header file
    Double inertia = computeInertia(dataset, labels, centroids);

    Std::cout << “\n”;
    Std::cout << “ Calculated Inertia: “ << inertia << “\n”;
    Std::cout << “\n”;

    Return 0;
}

