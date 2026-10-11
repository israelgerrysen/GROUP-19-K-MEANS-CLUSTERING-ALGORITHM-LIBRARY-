# Centroidinitializer Class Report 

## Classes created
- The class created was named `Centroidinitializer`

## Why?
- A starting centroid is need before the algorithm can begin.
- To remember the Value of `k`and keep its own random number generator, so the rest of the program does nothave to manage them.

## The Data it holds
### private
`k_`: The number of centroids to pick.
`gen_` : The Random number generator (`std::mt19937`).

### public
- The class defines two type names:
- `Point`: A vector of doubles.
- `Dataset`: A vector of points.

## What functions operate on that data?
### Constructors
`CentroidInitializer(k)` uses a random seed.
`CentroidInitializer(k, seed)` uses a fixed seed, so the results can be repeated.
`getK()` returns `k_`.
`setK(k)` changes `k_`.
`initialize(const Dataset& data)` picks `k` different random points from the dataset and returns them as the centroids. It shuffles the list of point positions (indices) and takes the first `k`, so no point is chosen twice. If the data is empty or `k` is invalid (k <= 0 or k larger than the number of points), it returns an empty result.

## Why some members are in private and others in public?
- `k_` and `gen_` are private because they are internal details. Outside code should not change  them directly. For example, `k_` can only be changed through `setK()`.
- The constructors, `getK()`, `setK()` and `initialize()`  are public because they are the only things other code needs to use.

## How the class is used by the rest of the program.
- The rest of the program creates a `CentroidInitializer` with a value for `k`, then calls `initialize(data)` on the dataset. The returned centroids are given to the next steps, such as distance calculation and cluster assignment.

- The class is checked by `testing_Centroid_intialization.cpp`, which tests invalid input, uniqueness of the centroids, `getK`/`setK`, and the same-seed case.