# Cluster Assignment Report

## 1. What class did you create?
I created the `ClusterAssignment` class.

## 2. Why?
After the centroids are chosen, K-Means must decide which cluster each data point belongs to. I made a class for this step so the assignment logic is in one place and can be repeated in every iteration of the algorithm. It uses `DistanceCalculator` to measure how close a point is to each centroid.

## 3. What data does it hold?
It holds no data. It has no member variables, because everything it needs is passed in as arguments. The class only defines two type names: `Point` (a `std::vector<double>`) and `Dataset` (a vector of points).

## 4. What functions operate on that data?
It has one function:
- **`assignClusters(data, centroids)`** returns a list of numbers, one for each data point. Each number is the index of the centroid that is closest to that point.

How it works:
1. For each point, it checks the distance to every centroid.
2. It keeps the centroid with the smallest distance.
3. It uses `squareddistance` instead of `distance`, because the nearest centroid is the same and it avoids the slower square root.
4. If two centroids are equally close, the one with the lower index wins.

It throws `std::invalid_argument` if the data is empty, the centroids are empty, or a point and a centroid have different dimensions. The input data is never changed.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
Everything is **public**, because there is no internal state to protect. The constructor is **deleted** (`ClusterAssignment() = delete`), so nobody can create an object. This makes it a utility class, like `DistanceCalculator`.

The rest of the program calls the function directly, with no object:

```cpp
std::vector<int> labels = ClusterAssignment::assignClusters(data, centroids);
```

The centroids come from `CentroidInitializer`. The labels are then used to update the centroids in the next step of K-Means. The class is checked by `testing_Cluster_Assignment.cpp`, which tests clear clusters, a point on a centroid, ties, a single centroid, 1-D and negative data, unchanged input, and the error cases.
