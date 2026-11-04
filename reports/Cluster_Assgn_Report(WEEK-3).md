## WEEK 3 PROGRESS REPORT

Project: K-Means Clustering Algorithm Library (C++)
Focus: Implementation of Cluster Assignment Logic and Application of Object-Oriented Programming Principles

## 1. Introduction

During the third week of the project, I continued working on the development of the K-Means Clustering Algorithm Library using C++. The main objective was to implement and test the cluster assignment component, which is responsible for allocating each data point to its nearest centroid based on the calculated distance.
In addition to implementing the assignment logic, I focused on improving the code structure through the application of object-oriented programming (OOP) principles. I also developed comprehensive unit tests to verify the correctness, reliability, and efficiency of the implemented functions.

## 2. Work Completed

The following activities were successfully completed during the week:

- Implementation of Cluster Assignment Logic: I completed the development of the Cluster_Assignment.cpp source file. The implementation includes the assignClusters function, which examines each data point, calculates its squared Euclidean distance from all available centroids, and assigns it to the cluster with the minimum distance.

- Input Validation and Error Handling: I introduced input validation mechanisms to improve the reliability of the function. The implementation checks whether the dataset and centroid collections are empty. If either is empty, the function throws a std::invalid_argument exception to prevent invalid operations.

- Development of Unit Tests: I created the testing_Cluster_Assignment.cpp file to evaluate the functionality and accuracy of the cluster assignment implementation. The tests cover several scenarios, including:

* Separation of clearly defined clusters using two-dimensional datasets.
* Assignment of points that lie exactly on a centroid.
* Handling of equal-distance cases, ensuring that ties are resolved in favour of the centroid with the lowest index.
* Assignment using a single centroid.
* Processing of one-dimensional datasets.
* Handling of negative coordinate values.
* Verification that the original dataset remains unchanged after cluster assignment.
  These tests helped confirm that the implementation behaves correctly under normal conditions and different edge cases.

## 3. Application of Object-Oriented Programming Concepts

During the development of the ClusterAssignment class, I considered how object-oriented programming principles could be applied to improve the organization, maintainability, and reusability of the library.

- Encapsulation: The ClusterAssignment class was implemented as a stateless utility class. A deleted default constructor (ClusterAssignment() = delete;) was introduced to prevent the creation of unnecessary class objects. This ensures that the functionality is accessed through static methods while maintaining a clear and organized public interface.

- Inheritance: Inheritance was not implemented in this component because the cluster assignment functionality is independent and does not currently require a shared base class. Its responsibilities are sufficiently specific to be handled by a standalone utility class.

- Polymorphism: Runtime polymorphism was not necessary for this implementation. Instead, the class uses static methods to provide its functionality. This approach is appropriate because the assignment operation does not require different implementations of a common virtual interface.

Overall, the implementation demonstrates how OOP concepts can be applied selectively, depending on the responsibilities and requirements of individual components.

## 4. Challenges Encountered

One of the main challenges encountered during the week was ensuring the accuracy of the distance calculations, particularly when dealing with floating-point values and points located at equal distances from multiple centroids.

Another challenge involved implementing a consistent tie-breaking mechanism to ensure that when two or more centroids have the same minimum distance from a data point, the centroid with the lowest index is selected.

Additionally, designing unit tests that covered both normal operating conditions and unusual input scenarios required careful consideration. However, developing the tests helped identify potential logical errors and improved the reliability of the implementation.

## 5. Conclusion

The third week marked significant progress in the development of the K-Means Clustering Algorithm Library. The cluster assignment component was successfully implemented, validated, and tested against various scenarios. The work also strengthened my understanding of static utility classes, encapsulation, exception handling, and unit testing in C++.

The successful completion of this component provides an important foundation for the next stage of development, where the cluster assignment functionality will be integrated into the main K-Means algorithm to support iterative centroid updates and cluster optimization.
