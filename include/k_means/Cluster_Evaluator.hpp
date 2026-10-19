#ifndef INERTIAEVALUATOR.HPP
#define INERTIAEVALUATOR.HPP

#include <vector>
#include <cmath>
#include <cstddef>


// DATA STRUCTURE DEFINITIONS
 

// Structure to represent a 2D data point
Struct Point {
    Double x;
    Double y;
};


// HELPER FUNCTIONS



Inline double calculateSquaredDistance(const Point& p1, const Point& p2) {
    Double dx = p1.x – p2.x;
    Double dy = p1.y – p2.y;
    Return (dx * dx) + (dy * dy);
}


// INERTIA EVALUATION FUNCTION



Inline double computeInertia(const std::vector<Point>& points, 
                              Const std::vector<int>& labels, 
                              Const std::vector<Point>& centroids) {
    
    Double totalInertia = 0.0;

    // Loop through every single data point in our dataset
    For (size_t i = 0; i < points.size(); ++i) {
        
        Int assignedCluster = labels[i];
        
        // Basic bounds check to prevent out-of-bounds errors with malformed labels
        If (assignedCluster >= 0 && static_cast<size_t>(assignedCluster) < centroids.size()) {
            Const Point& centroid = centroids[assignedCluster];
            
            // Add squared distance to running total
            totalInertia += calculateSquaredDistance(points[i], centroid);
        }
    }

    Return totalInertia;
}

#endif // INERTIAEVALUATOR.HPP

