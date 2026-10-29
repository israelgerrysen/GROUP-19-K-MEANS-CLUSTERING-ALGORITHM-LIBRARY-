# User Guide

## What this library does

This project is a reusable C++20 library that groups numeric observations into `k` clusters. It exposes the algorithm as small public modules for CSV loading, data preprocessing, feature scaling, centroid initialization, distance measurement, cluster assignment, centroid updates, empty-cluster repair, convergence detection, and inertia evaluation. The two programs in `examples/` show how to combine those modules.

The algorithm is unsupervised: it uses numeric features and does not require a target label. Feature values should be numeric and finite by the time they are scaled and clustered. K-Means is sensitive to feature scale, so scale features before distance-based clustering when their ranges differ.

## Requirements

- CMake 3.16 or newer.
- A C++20 compiler supported by CMake (for example, a recent GCC, Clang, or MSVC).
- Git is optional if the source was obtained as an archive.

The library has no third-party C++ runtime dependency. The example that reads `data/input/football.csv` requires that bundled data file or a path to another compatible CSV file.

## Build from a clean checkout

Run these commands from the project root. The generated `build/` directory is disposable and can be recreated at any time.

### Windows PowerShell

```powershell
cmake -S . -B build
cmake --build build --config Release
```

### Linux or macOS

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

Examples are enabled by default. To build only the library, configure with `-DKMEANS_BUILD_EXAMPLES=OFF`. Tests are enabled by CMake's `BUILD_TESTING` option, which defaults to `ON` when CTest is included; to omit them, configure with `-DBUILD_TESTING=OFF`.

## Run the examples

From the project root, run the generated programs:

```powershell
.\build\example_kmeans.exe
.\build\example_csv_clustering.exe
```

On Linux or macOS, use `./build/example_kmeans` and `./build/example_csv_clustering`. The CSV example accepts a CSV path as its first argument and selects zero-based columns 12 and 13 in the bundled football dataset:

```powershell
.\build\example_csv_clustering.exe .\data\input\football.csv
```

The in-memory example has fixed synthetic data and a fixed seed, so its initial centroids are repeatable. Both programs print cluster centroids, labels or counts, iteration count, and inertia as appropriate. Each example coordinates the public library components directly through `#include <k_means/k_means.hpp>`.

## Run the tests

Build first, then run CTest from the project root:

```sh
ctest --test-dir build --output-on-failure
```

CTest discovers one executable test for each major module. The tests can also be run through an IDE that understands the generated CMake project.

## Install and consume the library

Install to a chosen prefix (the example below uses a local `install/` directory):

```sh
cmake --install build --prefix install
```

The install includes the static library, public headers under `include/k_means/`, and CMake package files under `lib/cmake/KMeansLibrary/` (the library directory name can vary by platform). A consumer project can use the exported target:

```cmake
find_package(KMeansLibrary CONFIG REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE KMeansLibrary::kmeans_lib)
```

Set `CMAKE_PREFIX_PATH` to the installation prefix when it is not in a standard package location. Include the complete public API with `#include <k_means/k_means.hpp>`, or include a specific header such as `#include <k_means/ClusterAssignment.hpp>`.

## Minimal API example

This example shows the core assignment/update loop. For production use, also preprocess missing values, scale features, repair empty clusters, stop using the convergence detector, and evaluate the final assignments. The shipped complete example demonstrates that fuller workflow.

```cpp
#include <k_means/k_means.hpp>

#include <iostream>

int main() {
    using Dataset = CentroidInitializer::Dataset;
    const Dataset data{{1.0, 1.0}, {1.2, 0.9}, {8.0, 8.0}, {8.2, 7.9}};

    CentroidInitializer initializer(2, 42); // fixed seed for repeatability
    Dataset centroids = initializer.initialize(data);

    for (int iteration = 0; iteration < 20; ++iteration) {
        const auto labels = ClusterAssignment::assignClusters(data, centroids);
        const auto updated = CentroidUpdater::update(data, labels, centroids);
        centroids = updated;
    }

    for (const auto& centroid : centroids) {
        std::cout << '(' << centroid[0] << ", " << centroid[1] << ")\n";
    }
}
```

This intentionally small loop has a fixed iteration count and does not repair empty clusters. See `examples/example_kmeans.cpp` and `examples/example_csv_clustering.cpp` for complete workflows and the API reference for validation behavior.

## Limitations and usage notes

- K-Means uses Euclidean distance and numeric vectors; categorical data must be converted to numeric features before clustering.
- `DataLoader` reads a header row and numeric CSV cells. A non-numeric or non-finite cell is represented as NaN for preprocessing; it is not categorical encoding.
- `DataPreprocessor::oneHotEncode` appends encoded columns for a separately supplied category value per row. It does not parse a categorical CSV column itself.
- Missing values must be removed or imputed before scaling and clustering. Both examples use median imputation.
- Scaling changes the distance space. The example reports inertia in scaled feature space and inverse-transforms centroids for display.
- Plain K-Means can converge to different local results with different initial centroids. Pass a seed to `CentroidInitializer` for repeatable initialization.
- The library provides algorithm components rather than a single public `KMeans` estimator class; callers coordinate the steps. The end-to-end helper lives in `examples/` and is not installed as library API.
- `CentroidUpdater` leaves an empty cluster at its previous centroid. Call `handleEmptyClusters` after assignment when empty clusters need to be repopulated.

## Project layout

```text
include/k_means/   Public headers
src/               Library implementations
tests/             CTest test programs, one per module
examples/          Small client programs and example-only support
data/input/        Bundled CSV input used by the CSV example
reports/           Weekly contribution reports and diagrams
cmake/             CMake package configuration template
docs/              User, algorithm, and API documentation
build/             Generated build tree; do not treat as source
```

