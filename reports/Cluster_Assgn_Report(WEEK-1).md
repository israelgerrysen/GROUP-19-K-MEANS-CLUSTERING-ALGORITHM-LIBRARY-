## Completed

Worked on the cluster assignment component of the K-Means Clustering Algorithm Library in C++.

Created the Cluster_Assignment.hpp header file with the class declaration and function prototype.

Implemented the assignClusters() function to assign each data point to its nearest centroid.

Used squared Euclidean distance to compare data points with centroids and determine the closest cluster.

Added validation to handle empty datasets and empty centroid lists using std::invalid_argument.

Implemented logic to ensure that when two centroids have equal distances, the centroid with the lower index is selected.

## In Progress

Reviewing the implementation to ensure that the header and CPP files work correctly together.

Checking the integration with the distance calculation component.

Reviewing possible edge cases, including mismatched dimensions between data points and centroids.

## Challenges/Blockers

I had to understand how the distance calculation function works and how to use it when assigning data points to clusters.

I needed to ensure that the correct centroid is selected based on the minimum squared distance.

I also had to consider how to handle invalid inputs, such as empty datasets and empty centroid lists.

Testing is still needed to confirm that the implementation works correctly with the other components.

## Next Week

Test the cluster assignment function using different datasets and centroid values.

Check that the function handles invalid inputs and edge cases correctly.

Verify that the distance calculation component integrates properly with the cluster assignment files.

Fix any errors discovered during testing.

Review and clean up the code before submission.

## AI Use

Tool: ChatGPT

Purpose: Helped me understand the implementation of the cluster assignment component and review the C++ code.

Reason: I used it to get explanations about assigning data points to their nearest centroids, using squared distances, handling invalid inputs, and understanding how the header and CPP files work together.

## References

Project source files. (2026). Cluster_Assignment.hpp and Cluster_Assignment.cpp.

cppreference.com. (n.d.). std::vector. https://en.cppreference.com/w/cpp/container/vector

cppreference.com. (n.d.). std::invalid_argument. https://en.cppreference.com/w/cpp/error/invalid_argument
