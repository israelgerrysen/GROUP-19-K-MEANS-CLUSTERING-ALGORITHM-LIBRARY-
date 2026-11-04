## WEEK 2 PROGRESS REPORT

## 2. What class did you create?

I created a class called ClusterAssignment in C++. It is responsible for assigning each data point to its nearest centroid in the K-Means Clustering Algorithm Library.

The class is declared in Cluster_Assignment.hpp and its main implementation is written in Cluster_Assignment.cpp.

The class contains a static function called assignClusters() that returns a list of cluster labels, showing which centroid each data point belongs to.

## 2. Why did you create this class?

I created this class to implement the cluster assignment step of the K-Means clustering algorithm.

Its main purpose is to compare each data point with the available centroids, calculate the squared distance between them, and assign the data point to the closest centroid.

This helps the K-Means algorithm group similar data points into clusters based on their distances from the centroids.

I used squared Euclidean distance because it can identify the nearest centroid without calculating the square root, making the comparison simpler.

## 3. What data does it hold?

The class uses two main data types:

Point: A vector of double values representing one data point.

Dataset: A vector of points representing a collection of data points or centroids.

The assignClusters() function receives two datasets:

data: Contains the data points that need to be assigned to clusters.

centroids: Contains the current centroid positions used for comparison.

The function returns a std::vector<int> containing the cluster index assigned to each data point.

The class does not store permanent data members because it is designed as a utility class. It processes the supplied datasets and returns the assignments.

## 4. What functions operate on that data?

The main function is assignClusters().

It performs the following operations:

Checks whether the data points and centroids are empty.

Creates a vector to store the cluster assignments.

Loops through each data point.

Calculates the squared distance between the data point and each centroid using DistanceCalculator::squareddistance().

Identifies the centroid with the smallest distance.

Stores the index of the closest centroid as the cluster assignment.

Returns the completed vector of cluster labels.

The function also handles situations where two centroids have equal distances. In such cases, the centroid with the lower index is selected because the comparison uses the less-than (<) operator.

The function throws std::invalid_argument when the data or centroid dataset is empty.

It also relies on the distance calculation component to handle dimension mismatches.

## 5. Why are some members private and others public?

The ClusterAssignment class uses a simple public interface because it does not require internal object data or private member variables.

The Point and Dataset type definitions and the assignClusters() function are public so that other parts of the program can access and use them.

The constructor is deleted using ClusterAssignment() = delete; to prevent the creation of unnecessary objects.

This is because the class uses static functions, meaning the function can be called directly using the class name without creating an object.

For example:

ClusterAssignment::assignClusters(data, centroids);

This design makes the class easier to use and keeps its responsibility focused on assigning data points to clusters.

## 6. How is the class used by the rest of the program?

The Cluster Assignment class works as one of the components of the K-Means Clustering Algorithm Library.

It receives a dataset and a collection of centroids, uses the distance calculation component to compare them, and returns the cluster labels.

The returned labels can then be used by other parts of the K-Means algorithm to identify which data points belong to each cluster.

I also created a separate testing file called testing_Cluster_Assignment.cpp to check the functionality of the class.

The testing file includes Cluster_Assignment.hpp and uses the assignClusters() function to test different inputs and expected results.

## 7. How did you test the class?

I created a testing program containing 11 checks to examine the correctness of the cluster assignment function.

The tests cover the following cases:

Number of assignments: Checks that the function returns one cluster label for every data point.

Normal cluster assignment: Checks whether four data points are correctly assigned to two obvious clusters.

Point on a centroid: Checks whether a data point located exactly on a centroid is assigned to that centroid.

Equal distances: Checks whether the centroid with the lower index is selected when a data point is equally distant from two centroids.

Single centroid: Checks whether all data points are assigned to cluster zero when only one centroid is provided.

One-dimensional data: Checks whether the function works with one-dimensional points and preserves the order of centroid labels.

Negative coordinates: Checks whether the function correctly assigns data points containing negative values.

Input preservation: Checks that the original dataset is not modified during cluster assignment.

Empty centroids: Checks whether an std::invalid_argument exception is thrown when the centroid dataset is empty.

Empty data: Checks whether an std::invalid_argument exception is thrown when the data dataset is empty.

Dimension mismatch: Checks whether an std::invalid_argument exception is thrown when data points and centroids have different dimensions.

The testing program uses a helper function called require() to check whether each condition is satisfied. It also uses a throws() function to check whether the expected exceptions are generated.

The program is designed to display a message showing how many checks passed if all the tests succeed.

Testing status: The test cases have been written, but their successful execution has not yet been confirmed.

## 8. Challenges/Blockers

I had to understand how to connect the Cluster Assignment class with the Distance Calculation component.

I needed to ensure that each data point was assigned to the centroid with the smallest squared distance.

I had to consider how to handle equal distances between centroids so that the results remain consistent.

I also needed to consider invalid inputs, including empty datasets and dimension mismatches.

Another challenge was designing test cases that cover normal operations as well as unusual input conditions.

I also had to ensure that the original dataset remains unchanged after the assignment operation.

## 9. Next Week

Compile the Cluster Assignment implementation together with its required dependencies.

Run the testing program and confirm whether all 11 checks pass.

Fix any compilation errors or unexpected test failures.

Verify that dimension mismatch validation works correctly through the Distance Calculation component.

Test additional datasets with different numbers of points and centroids.

Check the integration of Cluster Assignment with the other components of the K-Means library.

Review and clean up the code before submission.

## 10. AI Use

Tool: ChatGPT

Purpose: Helped me understand and review the Cluster Assignment implementation and its testing program.

Reason: I used it to get explanations about how data points are assigned to their nearest centroids, how squared Euclidean distance is used, how cluster labels are generated, and how to test different conditions in C++. It also helped me understand the relationship between the header file, CPP implementation file, and testing file.

## 11. References

Project source file. (2026). Cluster_Assignment.hpp.

Project source file. (2026). Cluster_Assignment.cpp.

Project testing file. (2026). testing_Cluster_Assignment.cpp.

Project dependency. Distance_Calculation.hpp (used by the Cluster Assignment component).
