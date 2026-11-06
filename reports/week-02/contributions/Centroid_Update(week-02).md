# Week 2 Class Explanation: Centroid Update

## 1. What class did you create?
I created a class called `CentroidUpdater`. It calculates new centroids by finding the average of the points assigned to each cluster.

## 2. Why did you create it?
After K-Means assigns points to clusters, it needs to move each centroid to the average position of the points in that cluster. This class handles that update step in one place.

## 3. What data does the class hold?
The class does not store changing data in member variables. It defines two names for the data shapes it uses:

- `Point` means one data point, written as a list of numbers.
- `Dataset` means a list of points. It can represent the data or the centroids.

The update function receives the data points, their cluster labels, and the previous centroids as inputs.

## 4. What functions operate on that data?

- `update(data, assignments, currentCentroids)` is a public static function. It returns the new centroids by averaging the points in each cluster.
- The function checks that the inputs are valid. For example, each data point needs a cluster label, each label must match a centroid, and points must have matching feature counts.
- If a cluster has no points, its old centroid is kept.
- The constructor is deleted, which means the program cannot create a `CentroidUpdater` object. The class is used by calling its static function directly.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
The class's types and update function are public so other parts of the program can use them. It has no private or protected data members because it does not keep its own state. The inputs are passed to `update`, and the function returns a new dataset without changing the original inputs.

The rest of the program can call `CentroidUpdater::update(data, assignments, centroids)`. The returned centroids can then be used in the next K-Means step. The test file calls this function with normal and invalid examples to check its behavior.

## Header File Role
The header declares the class, its type names, the static function, and the deleted constructor. The `.cpp` file contains the steps that validate the input and calculate the averages.
