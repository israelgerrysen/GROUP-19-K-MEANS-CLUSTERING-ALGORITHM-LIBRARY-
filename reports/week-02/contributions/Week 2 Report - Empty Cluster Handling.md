# Week 2 Report
# OKOBOI REUBEN
# 25/U/08779/PS
# BCCE

# Class Structure and Implementation: Empty Cluster Handling

## 1. What class did you create?
A standalone class was not created; instead, the functionality is defined as a standalone free utility function inside the `EmptyCluster.hpp` and `EmptyCluster.cpp` module under the API function `handleEmptyClusters`.

## 2. Why?
During K-Means clustering iterations, initialization or assignment steps can result in empty clusters (clusters assigned zero data points). This module handles dataset stability by repairing empty clusters. It finds the point farthest from its assigned centroid in a cluster containing multiple data points, reassigns that point to the empty cluster, and updates the empty cluster's centroid coordinates to match the newly assigned point.

## 3. What data does it hold?
The module holds no state or persistent internal data members. It operates directly on reference parameters passed to it:
* `const std::vector<std::vector<double>>& data`: Read-only external dataset.
* `std::vector<std::vector<double>>& centroids`: Modifiable vector of cluster centroids.
* `std::vector<int>& assignments`: Modifiable vector of point assignment labels.

## 4. What functions operate on that data?
The module exposes one main function and utilizes internal helper logic:
* **`handleEmptyClusters`**: A standalone function accepting `data`, `centroids`, and `assignments`. It checks inputs, counts cluster populations, locates eligible donor clusters (with population > 1), finds the farthest point using Euclidean squared distance, and reassigns the point and updates the centroid.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
**Public vs. Private:**
* **Public API:** The function `handleEmptyClusters(...)` is publicly declared in `EmptyCluster.hpp` as part of the public interface.
* **Private/Internal Mechanics:** Within `EmptyCluster.cpp`, internal helper lambdas (such as `validatePoint` for checking dimensionality and finite double bounds) and local tracking structures (`counts` and `moved` vectors) are scope-isolated within the function implementation, preventing pollution of the global namespace.

**Usage by the Program:**
The rest of the program includes `EmptyCluster.hpp` and invokes the function directly without creating an object instance:
`handleEmptyClusters(data, centroids, assignments);`
It acts as a post-assignment repair step within the K-Means iteration process.