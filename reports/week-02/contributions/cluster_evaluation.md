# Week 2 report

## Overview
This report deconstructs the organization of the K-Means Inertia Evaluation program, as implemented in `Cluster_evaluation.cpp` and `Cluster_Evaluator.hpp`. It outlines the data structures used, their members, and how they interact to calculate the within-cluster sum of squares (inertia).


# **1. What class did you create?**
No class was created. In this program, the fundamental data structure created is `Point`. While defined using the `struct` keyword, in C++, a `struct` operates essentially as a class where members are public by default. 

# **2. Why?**
The `Point` structure was created to logically group the coordinates of a 2-dimensional space into a single unit. In a K-Means clustering algorithm, managing individual `x` and `y` variables for every calculation would be highly prone to error and messy. By encapsulating these into a `Point` type, we can easily create vectors of points and pass whole coordinates to our evaluation functions.

# **3. What data does it hold?**
The `Point` structure holds the following data members:
*   `double x`: Represents the x-coordinate of the data point.
*   `double y`: Represents the y-coordinate of the data point.

# **4. What functions operate on that data?**
The program utilizes standalone helper functions that take `Point` objects as arguments. These functions are:
*   `calculateSquaredDistance(const Point& p1, const Point& p2)`: Takes two `Point` objects and computes the squared Euclidean distance between them.
*   `computeInertia(const std::vector<Point>& points, const std::vector<int>& labels, const std::vector<Point>& centroids)`: Operates on vectors of `Point` objects to calculate the total sum of squares.

# **5. Why are some members private and others public? How is the class used by the rest of the program?**
*   **Public vs. Private:** All members of `Point` (`x` and `y`) are **public**. Because `Point` is designed as a simple "Plain Old Data" (POD) container without complex internal state logic or validation requirements, making the members public allows for direct, efficient access without the need of getter and setter methods.
*   **How it is used:** The `Point` structure is used as the foundational building block throughout the `main()` routine and the header file. The program instantiates `std::vector<Point>` to hold the raw `dataset`, the `goodCentroids`, and the `badCentroids`. It is continuously accessed during the `for` loops where the algorithm iterates through each data point to find the nearest centroid and ultimately calculate the system's total inertia.