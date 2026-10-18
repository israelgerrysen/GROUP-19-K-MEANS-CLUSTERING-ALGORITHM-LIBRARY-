#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "InertiaEvaluator.hpp"


// 1. DATA STRUCTURE DEFINITIONS
 

// Structure to represent a 2D data point
Struct Point {
    Double x;
    Double y;
};


// 2. HELPER FUNCTIONS


// Function to calculate the SQUARED Euclidean distance between two points.

Double calculateSquaredDistance(const Point& p1, const Point& p2) {
    Double dx = p1.x – p2.x;
    Double dy = p1.y – p2.y;
    Return (dx * dx) + (dy * dy);
}


// 3. INERTIA EVALUATION FUNCTION



Double computeInertia(const std::vector<Point>& points, 
                      Const std::vector<int>& labels, 
                      Const std::vector<Point>& centroids) {
    
    // Initialize total inertia accumulator to zero
    Double totalInertia = 0.0;

    // Loop through every single data point in our dataset
    For (size_t i = 0; i < points.size(); ++i) {
        
        // Find which cluster this point was assigned to
        Int assignedCluster = labels[i];
        
        // Retrieve the corresponding centroid for that cluster
        Const Point& centroid = centroids[assignedCluster];
        
        // Calculate the squared distance from the data point to its cluster centroid
        Double sqDist = calculateSquaredDistance(points[i], centroid);
        
        // Add this squared distance to our running total inertia sum
        totalInertia += sqDist;
    }

    // Return the final aggregated inertia value
    Return totalInertia;
}


// 4. MAIN PROGRAM & MOCK K-MEANS ROUTINE


Int main() {
    // Set standard output formatting for cleaner numbers
    Std::cout << std::fixed << std::setprecision(4);

    //  Define a dummy dataset of 2D points grouped into two loose areas
    Std::vector<Point> dataset = {
        {1.0, 1.0}, {1.5, 2.0}, {2.0, 1.5}, // Group A candidates
        {8.0, 8.0}, {8.5, 9.0}, {9.0, 8.5}  // Group B candidates
    };

    //  Define K (number of clusters)
    Int k = 2;

    //  Simulate cluster centroids (in a real app, these come from K-Means convergence)
    // Let’s deliberately test two scenarios: Good Centroids vs. Bad Centroids
    
    // Scenario 1: Well-positioned centroids right in the middle of each group
    Std::vector<Point> goodCentroids = {
        {1.5, 1.5}, // Centroid for Group A
        {8.5, 8.5}  // Centroid for Group B
    };

    // Scenario 2: Poorly positioned centroids (shifted off-center)
    Std::vector<Point> badCentroids = {
        {4.0, 4.0}, 
        {5.0, 5.0}
    };

    // Assign each point to the nearest centroid (Standard K-Means assignment step)
    Std::vector<int> labels(dataset.size());

    For (size_t i = 0; i < dataset.size(); ++i) {
        Double minDistance = std::numeric_limits<double>::max();
        Int bestCluster = 0;

        // Find closest centroid for point i
        For (int c = 0; c < k; ++c) {
            Double dist = calculateSquaredDistance(dataset[i], goodCentroids[c]);
            If (dist < minDistance) {
                minDistance = dist;
                bestCluster = c;
            }
        }
        Labels[i] = bestCluster;
    }

  
    Double inertiaGood = computeInertia(dataset, labels, goodCentroids);

--
    For (size_t i = 0; i < dataset.size(); ++i) {
        Double minDistance = std::numeric_limits<double>::max();
        Int bestCluster = 0;

        For (int c = 0; c < k; ++c) {
            Double dist = calculateSquaredDistance(dataset[i], badCentroids[c]);
            If (dist < minDistance) {
                minDistance = dist;
                bestCluster = c;
            }
        }
        Labels[i] = bestCluster;
    }


    Double inertiaBad = computeInertia(dataset, labels, badCentroids);

    // Output Results
    Std::cout << “\n”;
    Std::cout << “       K-MEANS INERTIA EVALUATION         \n”;
    Std::cout << “\n”;
    Std::cout << “Inertia with WELL-PLACED centroids: “ << inertiaGood << “\n”;
    Std::cout << “Inertia with POOR-PLACED centroids: “ << inertiaBad  << “\n”;
    Std::cout << “\n”;


    Return 0;
}

