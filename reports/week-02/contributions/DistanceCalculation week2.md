#SEBBOWA MASAMBILA ABRAHAM 25/U/04087/PS


# Distance Calculation Report
## 1. What class did you create?
I created a class called `DistanceCalculator`. It has functions for measuring the distance between two points.

## 2. Why did you create it?
K-Means needs to compare data points with centroids to find which centroid is closest. This class keeps the distance calculations in one place so other parts of the program can use them.

## 3. What data does the class hold?
The class does not store changing data in member variables. It defines a type name called `Point`, which means a list of decimal numbers (`std::vector<double>`). The points are passed into its functions when they are called.

## 4. What functions operate on that data?

- `distance(p1, p2)` returns the Euclidean distance. It calculates the square root of the sum of the squared differences between matching values.
- `squareddistance(p1, p2)` returns the sum of those squared differences without taking the square root. This can save work when the program only needs to compare distances.
- Both functions check that the points have the same number of values and contain finite numbers. Invalid input causes `std::invalid_argument` to be thrown.

Both functions are `static`, so they can be called using the class name without creating an object. The constructor is deleted to prevent objects from being created.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
The `Point` type and the two distance functions are public so other parts of the program can use them. There are no private or protected data members because the class does not store its own data.

The rest of the program can call `DistanceCalculator::distance(point, centroid)` or `DistanceCalculator::squareddistance(point, centroid)`. The returned number tells the caller how far apart the two points are. The test file calls these functions with examples and checks that invalid inputs are rejected.

## Header File Role
The header declares the class, its `Point` type, and its public functions. The `.cpp` file contains the formulas and input checks.

