# GROUP-19-K-MEANS-CLUSTERING-ALGORITHM-LIBRARY-

A reusable C++20 library that groups numeric data points into `k` clusters using the K-Means algorithm. The library separates data preparation, clustering operations, convergence checks, empty-cluster handling, and cluster evaluation into public modules.

This project was developed for **Machine Learning 11: Design and Implementation of the K-Means Clustering Algorithm in C++**.

## Project objective

Design and implement a reusable C++ library that demonstrates object-oriented design, a clear public API, appropriate algorithms and data structures, input validation, professional project organization, testing, and documentation. This library provides the components needed to run K-Means while allowing each major step to be used and tested separately.

## Main features

- Load numeric data from CSV, optionally selecting and ordering zero-based columns.
- Clean data by dropping columns or rows with missing values, or impute missing values with the mean, median, or mode.
- Append one-hot encoded columns from category values supplied separately from the numeric matrix.
- Scale features with MinMax scaling or z-score standardization, and inverse-transform results.
- Initialize centroids by selecting distinct input rows, with optional fixed random seed for repeatability.
- Calculate Euclidean and squared Euclidean distances and assign points to their nearest centroid.
- Update centroids to the means of their assigned points.
- Detect convergence by centroid movement, unchanged assignments, or maximum iteration count.
- Repair empty clusters by moving eligible farthest points into them.
- Evaluate clustering with inertia (the sum of squared distances to assigned centroids).
- Build as a reusable CMake library, with example programs, CTest tests, install rules, and an exported CMake package target.

## How K-Means works

1. Load or provide a numeric dataset.
2. Remove or impute missing values and scale features as needed.
3. Select `k` initial centroids from distinct data rows.
4. Assign each point to its nearest centroid.
5. Repair any empty clusters, then update each centroid to the mean of its assigned points.
6. Repeat assignment and update until centroids or assignments stabilize, or the iteration limit is reached.
7. Assign points against the final centroids and calculate inertia.

The library exposes these as components rather than a single public estimator class. The example helper in `examples/kmeans_example_utils.hpp` demonstrates how to coordinate the steps.

## Project structure

```text
project-root/
├── CMakeLists.txt                 CMake build, test, and install configuration
├── README.md                      Project overview and quick start
├── cmake/                         CMake package configuration template
├── data/input/                    CSV input used by the CSV example
├── docs/                          User guide, algorithm workflow, and API reference
├── examples/                      Example programs and example-only helper
├── include/k_means/               Public C++ headers
├── reports/                       Weekly reports, contributions, and diagrams
├── src/                           Library implementation files
├── tests/                         Module tests registered with CTest
└── build/                         Generated build output (created by CMake)
```

Each public header in `include/k_means/` declares a module implemented by a corresponding file in `src/`. Tests include public headers and link to the library target. The examples also link to the library; `kmeans_example_utils.hpp` is private example support and is not part of the installed API.

## Requirements

- CMake 3.16 or newer.
- A C++20 compiler supported by CMake (for example, a recent GCC, Clang, or MSVC).
- No third-party C++ library dependency.

## Build

Run these commands from the project root.

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

Examples are built by default. Configure with `-DKMEANS_BUILD_EXAMPLES=OFF` to omit them. Tests are enabled by default through CTest; use `-DBUILD_TESTING=OFF` to omit test targets.

## Run the examples

Run from the project root so that the bundled CSV path resolves:

```powershell
.\build\example_kmeans.exe
.\build\example_csv_clustering.exe
```

The CSV example accepts a file path as its first argument. By default it reads `data/input/football.csv` and selects zero-based columns 12 and 13 (home and away goal counts):

```powershell
.\build\example_csv_clustering.exe .\data\input\football.csv
```

On Linux or macOS, execute `./build/example_kmeans` and `./build/example_csv_clustering` instead. The in-memory example uses a fixed seed. Both examples report clustering output; the CSV example also reports cluster counts.

## Use the library

The public headers are included using the `k_means/` prefix. This short example illustrates centroid initialization, assignment, and update:

```cpp
#include "k_means/Centroid_initialization.hpp"
#include "k_means/Centroid_Update.hpp"
#include "k_means/ClusterAssignment.hpp"

int main() {
    using Dataset = CentroidInitializer::Dataset;
    const Dataset data{{1.0, 1.0}, {1.2, 0.9}, {8.0, 8.0}, {8.2, 7.9}};

    CentroidInitializer initializer(2, 42U);
    Dataset centroids = initializer.initialize(data);
    for (int iteration = 0; iteration < 20; ++iteration) {
        const auto labels = ClusterAssignment::assignClusters(data, centroids);
        centroids = CentroidUpdater::update(data, labels, centroids);
    }
}
```

This compact snippet uses a fixed iteration count and omits preprocessing and empty-cluster repair. See `examples/example_kmeans.cpp` and `examples/kmeans_example_utils.hpp` for a fuller workflow, or the [user guide](docs/USER_GUIDE.md) and [API reference](docs/API_REFERENCE.md) for details. Invalid input is generally reported with standard exceptions such as `std::invalid_argument`.

## Install and use from another CMake project

Install the library to a chosen prefix:

```sh
cmake --install build --prefix install
```

Then link the exported CMake target in a consumer project:

```cmake
find_package(KMeansLibrary CONFIG REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE KMeansLibrary::kmeans_lib)
```

If the installation prefix is not in a standard location, set `CMAKE_PREFIX_PATH` to that prefix when configuring the consumer project. Public headers install under `include/k_means/`.

## Run the tests

Build the project, then run all registered tests:

```sh
ctest --test-dir build --output-on-failure
```

The CMake project registers separate tests for centroid initialization, centroid update, assignment, evaluation, convergence, CSV loading, preprocessing, distance calculation, empty-cluster handling, and feature scaling.

## Limitations and notes

- K-Means operates on finite numeric features and uses Euclidean distance. Categorical values must be encoded as numeric features before clustering.
- `DataLoader` treats the first row as a header. Invalid or non-finite numeric cells become NaN for later preprocessing; it does not perform categorical parsing.
- `DataPreprocessor::oneHotEncode` appends columns from a separate category string per row. It does not read categorical columns from CSV.
- Missing values should be removed or imputed before scaling or clustering. The example helper uses median imputation.
- Feature scaling changes the distance space. The complete example reports inertia in scaled feature space and inverse-transforms centroids for display.
- K-Means can find different local solutions from different initial centroids. Use a fixed seed for repeatable initialization.
- `CentroidUpdater` leaves a centroid unchanged when its cluster has no points. Call `handleEmptyClusters` during the iteration when empty clusters should be repopulated.
- The library consists of algorithm components; callers coordinate the sequence. The end-to-end helper in `examples/` is not installed as public library API.

## Documentation

- [User guide](docs/USER_GUIDE.md) — requirements, build, install, examples, and tests.
- [Algorithm and workflow](docs/ALGORITHM.md) — module responsibilities and iteration flow.
- [API reference](docs/API_REFERENCE.md) — headers, methods, input rules, and exceptions.

## License

The project's original code is released under the [MIT License](LICENSE). The bundled `football.csv` has no source or license record in the repository and is **not** covered by the code license;

## Team contributions

Weekly module contribution records are kept under `reports/week-*/contributions/`.

| NAME | REG NO. | PROGRAMME |
|---|---|---|
| BUSULWA GERRYSON ISRAEL | 25/U/0826 | BELE |
| SSEGAWA JASIFA | 25/U/08782/PS | BCCE |
| OKOBOI REUBEN | 25/U/08779/PS | BCCE |
| SHAWN NANTUMBWE SEBULIBA | 25/U/0858 | BELE |
| NANDYOWA PATIENCE VALERIA | 25/U/0851 | BELE |
| NAKAWEESA LINDA LUCY | 25/U/02658/PS | BCCE |
| SEBBOWA MASAMBIRA ABRAHAM | 25/U/04087/PS | BCCE |
| DUMO MOSES | 21/X/20072/PS | BELE |

### Team collaboration

The project stores weekly reports and module contribution notes under `reports/`.

### AI-use declaration

- **Tool:** OpenAI.
- **Purpose:** Assisted with research on the K-means clustering algorithm,guidence on CMake/build setup, testing the algorithm and debugging to ensure the algorithm works without errors.
- **Reason:** To provide guidence in research to ensure proper understanding of the logic behind the algorithm and provide guidance on the reusable error-free library.

