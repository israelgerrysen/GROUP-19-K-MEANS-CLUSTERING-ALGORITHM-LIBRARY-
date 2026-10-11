# Distance Calculation Report

## 1. What class did you create?
I created the `DistanceCalculator` class.

## 2. Why?
K-Means needs to measure how far a point is from a centroid, so it can decide which cluster the point belongs to. I put this in its own class so the distance code is in one place and can be reused by other steps, such as cluster assignment and cluster evaluation.

## 3. What data does it hold?
It holds no data. It has no member variables, because a distance only depends on the two points that are passed in. The class only defines one type name: `Point`, which is a `std::vector<double>` (a list of feature values).

## 4. What functions operate on that data?
Both functions are `static` and take two points:
- **`distance(p1, p2)`** returns the Euclidean distance: the square root of the sum of the squared differences.
- **`squareddistance(p1, p2)`** returns the same value without the square root. It is faster, and it is enough when we only need to compare distances, such as finding the nearest centroid.

If the two points have a different number of dimensions, the functions throw `std::invalid_argument`.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
Everything is **public**, because there is no internal state to protect. The constructor is **deleted** (`DistanceCalculator() = delete`), so nobody can create an object. This makes it a utility class.

The rest of the program calls the functions directly, with no object:

```cpp
double d = DistanceCalculator::distance(point, centroid);
```

It is used during cluster assignment (to find the nearest centroid) and cluster evaluation. The class is checked by `testing_Distance_Calculation.cpp`, which tests known distances (such as the 3-4-5 triangle), identical points, negative values, different dimensions, and the error for different dimensions.