# GROUP-19-K-MEANS-CLUSTERING-ALGORITHM-LIBRARY-

A small, class-based C++ library that implements the K-Means clustering algorithm. K-Means groups data points into `k` clusters so that points in the same cluster are close to each other.

This project was built for **Machine Learning 11: Design and Implementation of the K-Means Clustering Algorithm in C++**.

## How K-Means works

1. **Prepare** the data: load it, clean it and scale the features.
2. **Initialize** `k` starting centroids by picking random data points.
3. **Assign** every point to its nearest centroid.
4. **Update** every centroid by moving it to the mean of its points.
5. **Repeat** steps 3 and 4 until the clusters stop changing (convergence).
6. **Evaluate** how good the clusters are.

## Modules

Each step is a separate class, so every part can be tested on its own.

| Step | Class | What it does | Status |
|---|---|---|---|
| Dataset loading | `DataLoader` | Loads the dataset | Done |
| Data preprocessing | `DataPreprocessor` | Prepares and cleans the data | Done |
| Feature scaling | `FeatureScaler` | Puts features on a similar scale | Done |
| Centroid initialization | `CentroidInitializer` | Picks `k` unique random data points as starting centroids | Done |
| Distance calculation | `DistanceCalculator` | Measures the distance between two points | Done |
| Cluster assignment | `ClusterAssignment` | Gives each point the index of its nearest centroid | Done |
| Centroid update | `CentroidUpdater` | Moves each centroid to the mean of its points | Done |
| Convergence detection | `ConvergeDetector` | Decides when to stop repeating | Done |
| Empty cluster handling | `EmptyClusterHandler` | Fixes clusters that end up with no points | Done |
| Cluster evaluation | `ClusterEvaluator` | Scores the final clusters | In progress |

## Project structure

```
CPP PROJECT/
├── include/                              Header files (.hpp): class declarations
│   ├── k-means_cluster.hpp               Umbrella header that includes all the modules
│   ├── DataLoader.hpp                    DataLoader
│   ├── DataPreprocessor.hpp              DataPreprocessor
│   ├── feature_scaler.hpp                FeatureScaler
│   ├── Centroid_initialization.hpp       CentroidInitializer
│   ├── Distance_Calculation.hpp          DistanceCalculator
│   ├── Cluster_Assignment.hpp            ClusterAssignment
│   └── Centroid_Update.hpp               CentroidUpdater
│   └── Converge_detector.hpp             ConvergenceDetector
│   └── Cluster_Evaluator.hpp             ClusterEvaluator
│
├── src/                                  Implementation files (.cpp): the code
│   ├── data_loader.cpp                   DataLoader
│   ├── data_preprocessor.cpp             DataPreprocessor
│   ├── feature_scaler.cpp                FeatureScaler
│   ├── Centroid_initialization.cpp       CentroidInitializer
│   ├── Distance_calculation1.cpp         DistanceCalculator
│   ├── Cluster_Assignment.cpp            ClusterAssignment
│   └── Centroid_Update.cpp               CentroidUpdater
│
├── testing_files/                        Test programs, one per module
│   ├── testing_data_loader.cpp           tests DataLoader
│   ├── testing_data_preprocessor.cpp     tests DataPreprocessor
│   ├── testing_feature_scaler.cpp        tests FeatureScaler
│   ├── testing_Centroid_intialization.cpp  tests CentroidInitializer
│   ├── testing_Distance_Calculation.cpp  tests DistanceCalculator
│   ├── testing_Cluster_Assignment.cpp    tests ClusterAssignment
│   └── testing_Centroid_Update.cpp       tests CentroidUpdater
│
└── README.md                             This file
```

How the files fit together:
- Every class has a **header** in `include/`, an **implementation** in `src/` and a **test** in `testing_files/`.
- A test file includes the header of its class, and it is compiled together with the matching `.cpp` file from `src/`.
- `Cluster_Assignment.hpp` includes `Distance_Calculation.hpp`, so the `ClusterAssignment` test also needs `Distance_calculation1.cpp`.
- The file names above for `CentroidInitializer`, `DistanceCalculator`, `ClusterAssignment` and `CentroidUpdater` are the exact names used in the code. The names for the data loader, preprocessor and scaler files (apart from `feature_scaler.hpp`) and for `k-means_cluster.hpp` are placeholders: rename them to match your real files.
- Files for convergence detection, empty cluster handling and cluster evaluation will be added to the same three folders when those modules are finished.

## Core types

All modules use the same two type names:

```cpp
using Point   = std::vector<double>;   // one data item: one number per feature
using Dataset = std::vector<Point>;    // a list of points
```

A centroid is just a `Point`, so the centroids are also a `Dataset`.

## Class details

### `CentroidInitializer`
Picks `k` different random points from the data as the starting centroids.

```cpp
CentroidInitializer init(3);          // random seed: different result every run
CentroidInitializer init(3, 42);      // fixed seed: repeatable result
auto centroids = init.initialize(data);
```

- Has private data (`k_` and `gen_`, the random generator) and public functions: `getK()`, `setK()` and `initialize()`.
- Returns an empty result if the data is empty or `k` is not between 1 and the number of points.

### `DistanceCalculator`
A utility class. All functions are static and no object is needed.

```cpp
double d  = DistanceCalculator::distance(a, b);          // Euclidean distance
double d2 = DistanceCalculator::squareddistance(a, b);   // no square root, faster
```

- Use `squareddistance` when you only need to compare distances, such as finding the nearest centroid.
- Throws `std::invalid_argument` if the points have different dimensions.

### `ClusterAssignment`
A utility class. Gives each point the index of its closest centroid.

```cpp
std::vector<int> labels = ClusterAssignment::assignClusters(data, centroids);
```

- `labels[i]` is the cluster index of `data[i]`.
- If two centroids are equally close, the one with the lower index wins.
- Throws `std::invalid_argument` if the data or centroids are empty, or if the dimensions differ.

### `CentroidUpdater`
A utility class. Moves each centroid to the mean of the points assigned to it.

```cpp
auto newCentroids = CentroidUpdater::update(data, labels, centroids);
```

- The inputs are not changed. A new list of centroids is returned.
- A cluster with no points keeps its old centroid (fixing this is the job of `EmptyClusterHandler`).
- Throws `std::invalid_argument` if the data or centroids are empty, if there is not one label per point, if a label is out of range, or if the dimensions differ.

## Example

A small example that uses the finished modules. This is a sketch with a fixed number of rounds; automatic stopping will come with convergence detection.

```cpp
#include "Centroid_initialization.hpp"
#include "Cluster_Assignment.hpp"
#include "Centroid_Update.hpp"
#include <iostream>

int main() {
    CentroidInitializer::Dataset data = {
        {1, 1}, {1.5, 2}, {2, 1},        // a group near (1.5, 1.5)
        {8, 8}, {9, 9}, {8.5, 9}         // a group near (8.5, 8.7)
    };

    CentroidInitializer init(2, 42);                 // k = 2, fixed seed
    auto centroids = init.initialize(data);

    for (int round = 0; round < 10; ++round) {
        auto labels = ClusterAssignment::assignClusters(data, centroids);
        centroids   = CentroidUpdater::update(data, labels, centroids);
    }

    for (const auto& c : centroids) {
        std::cout << "(" << c[0] << ", " << c[1] << ")\n";
    }
}
```

## Building and testing

Requires a C++17 compiler such as `g++`. Each module has its own test program. These commands are run from the project folder, with the headers in `include/`, the sources in `src/` and the tests in `testing_files/`.

```
g++ -std=c++17 -I include testing_files/testing_Centroid_intialization.cpp src/Centroid_initialization.cpp -o test_centroid
g++ -std=c++17 -I include testing_files/testing_Distance_Calculation.cpp src/Distance_calculation1.cpp -o test_distance
g++ -std=c++17 -I include testing_files/testing_Cluster_Assignment.cpp src/Cluster_Assignment.cpp src/Distance_calculation1.cpp -o test_cluster
g++ -std=c++17 -I include testing_files/testing_Centroid_Update.cpp src/Centroid_Update.cpp -o test_update
```

Run each program after it compiles (on Windows PowerShell, use `.\test_centroid.exe`). Each test prints a message when all its checks pass.

Tips:
- `ClusterAssignment` uses `DistanceCalculator`, so its test also needs `Distance_calculation.cpp`.
- If a folder name has spaces, put the path in quotes.
- If a compile fails, an old `.exe` may still be there. Run the test only when the compile succeeds.

## Design notes

- **One class per step**, so each part can be understood and tested separately.
- **Utility classes** (`DistanceCalculator`, `ClusterAssignment`, `CentroidUpdater`) have no stored data. Their constructors are deleted and their functions are static.
- **Input checks**: invalid input throws `std::invalid_argument` instead of giving wrong results quietly.
- **No hidden changes**: the functions do not modify the data you pass in.

## Team

|NAME | REG NO.| PROGRAMME |
|---|---|---|
| BUSULWA GERRYSON ISRAEL | 25/U/0826 | BELE |
| SSEGAWA JASIFA | 25/U/08782/PS | BCCE |
| OKOBOI REUBEN | 25/U/08779/PS | BCCE |
| SHAWN NANTUMBWE SEBULIBA | 25/U/0858 | BELE |
| NANDYOWA PATIENCE VALERIA | 25/U/0851 | BELE |
| NAKAWEESA LINDA LUCY | 25/U/02658/PS | BCCE |
| SEBBOWA MASAMBIRA ABRAHAM | 25/U/04087/PS | BCCE |
| DUMO MOSES | 21/X/20072/PS | BELE|
