# Week 2 Report: Centroid Update

## 1. What class did you create?
I created the `CentroidUpdater` class.

## 2. Why?
In K-Means, after every point is given to its nearest centroid, each centroid must move to the average (mean) of its points. I made a class for this step so the update logic is in one place. It is the second step that K-Means repeats, after `ClusterAssignment`.

## 3. What data does it hold?
It holds no data. It has no member variables, because everything it needs is passed in as arguments. The class only defines two type names:
- `Point`: a `std::vector<double>`, one number for each feature.
- `Dataset`: a `std::vector<Point>`, a list of points. It is used for both the data and the centroids.

## 4. What functions operate on that data?
It has one function:
- **`update(data, assignments, currentCentroids)`** returns the new centroids.

How it works:
1. It checks the input and throws `std::invalid_argument` if the data or centroids are empty, if there is not one label per point, if a label is outside the cluster range, or if the dimensions differ.
2. It adds up the points of each cluster and counts them.
3. It divides each total by the count to get the new centroid (the mean).
4. A cluster with no points keeps its old centroid, which also avoids dividing by zero.

The inputs are never changed. The function builds and returns a new list of centroids.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
Everything is **public**, because the class has no internal data to protect. The constructor is **deleted** (`CentroidUpdater() = delete`), so nobody can create an object. This makes it a utility class, like `DistanceCalculator` and `ClusterAssignment`.

The rest of the program calls the function directly, with no object:

```cpp
auto newCentroids = CentroidUpdater::update(data, assignments, centroids);
```

The `assignments` come from `ClusterAssignment`, and the starting `centroids` come from `CentroidInitializer`. The new centroids are then used in the next round of the K-Means loop.

The class is checked by `testing_Centroid_Update.cpp`, which has 17 checks. It tests the mean of each cluster, a single cluster, a cluster with one point, an empty cluster, 1-D and negative values, labels that are not in order, unchanged inputs, and the error cases.
