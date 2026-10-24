NANDYOWA PATIENCE VALERIA 25/U/0851
# Week 2 Progress Report

## Class Structure and Implementation: Convergence Detection

### 1. What class did you create?
I created the `ConvergenceDetector` class.

### 2. Why?
K-Means needs to know when to stop looping. Instead of repeating that check in several places, I put it in one class. It handles the two usual stopping rules (centroids that barely move, and assignments that no longer change) and also a cap on the number of iterations, so the rest of the library doesn't have to reimplement any of this.

### 3. What data does it hold?
Two private members:
- `double tolerance_`: how far a centroid can move between iterations and still count as settled.
- `int maxIterations_`: an upper limit on the number of iterations, so a run that never settles still ends.

It doesn't store the dataset or the centroids. Those get passed in as arguments each time a function is called.

### 4. What functions operate on that data?
- `centroidsConverged(oldCentroids, newCentroids)` returns true when no centroid has moved more than `tolerance_`. It returns false if the number of centroids changed, or if a centroid has turned into NaN (which can happen with an empty cluster). If two matching centroids have different dimensions it throws `std::invalid_argument`.
- `assignmentsConverged(oldAssignments, newAssignments)` returns true when the two label vectors are identical.
- `shouldStop(...)` returns true if `currentIteration >= maxIterations_`, or if either of the two checks above passes.
- Getters and setters for `tolerance_` and `maxIterations_`. The setters (and the constructor) throw `std::invalid_argument` for a negative or non-finite tolerance, or for a max iteration count below 1.

There is also a private static helper, `euclideanDistance`, which the centroid check uses to measure how far each centroid moved.

### 5. Why are some members private and others public? How is the class used by the rest of the program?

Public vs. private:
The two settings are private, so the only way to change them is through the constructor or the setters, and both of those check the value. That means nobody can leave the object with a negative tolerance or zero iterations. The functions that answer "should we stop?" are public because they are what the K-Means driver actually calls.

Usage by the program:
A typical K-Means loop keeps the previous centroids and assignments, computes the new ones, and then asks the detector:

```cpp
ConvergenceDetector detector(1e-4, 300);
...
if (detector.shouldStop(oldCentroids, newCentroids,
                        oldAssignments, newAssignments, iter)) {
    break;
}
```

The detector never owns any data. It only looks at values the main algorithm already has. It also just compares `iter` to `maxIterations_`, so whether the loop counts from 0 or from 1 is up to the loop.
