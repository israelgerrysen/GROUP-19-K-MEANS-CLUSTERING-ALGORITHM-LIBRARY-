# BUSULWA GERRYSON ISRAEL 25/U/0826 BELE

# Centroidinitializer Class Report (week 02)

# Week 2 Class Explanation: Centroid Initialization

## 1. What class did you create?
I created a class called `CentroidInitializer`. It prepares the starting centroids for the K-Means algorithm by choosing `k` different points from the dataset.

## 2. Why did you create it?
K-Means needs starting centroids before it can group the data. This class keeps the centroid selection work in one place, so the rest of the program can ask for starting points without handling the selection steps itself.

## 3. What data does the class hold?
The class stores two private pieces of data:

- `k_`: the number of centroids to choose.
- `gen_`: a random number generator used to shuffle the data point choices.

The header also defines two helpful names for the data shapes:

- `Point` means a list of numbers for one data point.
- `Dataset` means a list of points.

## 4. What functions operate on that data?

- `CentroidInitializer(int k)` creates the initializer with a requested number of centroids and random choices.
- `CentroidInitializer(int k, unsigned int seed)` creates it with a seed. Reusing the same seed makes the selection repeatable.
- `getK()` returns the current number of centroids.
- `setK(int k)` changes that number, as long as it is valid.
- `initialize(const Dataset& data)` chooses and returns `k` different data points for the initial centroids. It reports an error for invalid input, such as an empty dataset or an invalid `k`.

The header declares these functions. Their working code is in `Centroid_initialization.cpp`.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
The functions are public so other parts of the program can create and use a `CentroidInitializer`. The stored values `k_` and `gen_` are private so other code cannot change them directly. Instead, it uses the class's functions, which help keep the class in a valid state.

The rest of the program can create an initializer, pass it a dataset through `initialize(data)`, and use the returned points as the starting centroids. The test file checks that the class selects the right number of distinct points, gives repeatable results when seeded, and rejects invalid inputs.

## Header File Role
The header file describes the class's public names, functions, and private data. It tells other source files how to use the class. The `.cpp` file contains the detailed steps that make the functions work.
