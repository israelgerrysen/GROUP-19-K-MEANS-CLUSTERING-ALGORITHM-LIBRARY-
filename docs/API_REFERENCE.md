# Public API Reference

All headers are installed under `include/k_means/` and should be included with the `k_means/` prefix. The library is built as the CMake target `KMeansLibrary::kmeans_lib`. The project requires C++20.

## Shared data representation

Most clustering methods represent observations as `std::vector<std::vector<double>>`. Each inner vector is a point, and each coordinate is a feature. Feature counts must be consistent across points. `CentroidInitializer`, `CentroidUpdater`, `ClusterAssignment`, and `ClusterEvaluator` expose their own `Point`/`Dataset` aliases; use compatible vector types between modules.

## Data input and preparation

### `DataLoader` — `k_means/DataLoader.hpp`

```cpp
static std::vector<std::vector<double>> loadCSV(
    const std::string& filename,
    const std::vector<std::size_t>& selectedColumns = {});
```

The first CSV row is treated as a header and is not returned. With an empty `selectedColumns`, all fields are loaded. Otherwise, selected zero-based column indexes are returned in the caller's requested order. Empty lines are skipped. Unparseable, non-finite, or blank numeric values become NaN. Quoted fields and doubled quotes are handled; each data row must have the header's number of fields. Throws `std::runtime_error` when the file cannot be opened, `std::invalid_argument` for empty/invalid CSV structure, and `std::out_of_range` for an invalid selected column.

### `DataPreprocessor` — `k_means/DataPreprocessor.hpp`

All methods modify the matrix passed by non-const reference:

- `dropColumn(matrix, columnIndex)` removes a zero-based column; invalid indexes throw `std::out_of_range`.
- `dropRowsWithMissingData(matrix)` removes any row containing NaN.
- `fillMissingWithMean(matrix)`, `fillMissingWithMedian(matrix)`, and `fillMissingWithMode(matrix)` replace NaN values independently within each column. A column that is entirely missing cannot be imputed and throws `std::invalid_argument`.
- `oneHotEncode(matrix, categories)` appends one binary column for each distinct string in the supplied per-row `categories` vector. There must be exactly one category string per matrix row. It does not replace an existing numeric column or read categories from a CSV.

Rows must be rectangular. Infinite values are rejected. These routines specifically treat NaN as missing; use finite values for clustering.

### `FeatureScaler` — `k_means/feature_scaler.hpp`

```cpp
FeatureScaler scaler(FeatureScaler::Method::MinMax); // default
// FeatureScaler::Method::Standard is z-score standardization.
scaler.fit(data);
auto scaled = scaler.transform(data);
auto originalScale = scaler.inverse_transform(scaled);
```

`fit_transform(data)` combines `fit` and `transform`; `is_fitted()` reports whether fit succeeded. MinMax maps each fitted feature to `[0, 1]`; Standard subtracts the fitted population mean and divides by fitted population standard deviation. A constant feature uses scale 1, so its transformed values are zero and inverse transformation restores the constant offset. Input must be nonempty, rectangular, and finite. Transform operations require a fitted scaler and the same feature count used during fitting. Invalid data throws `std::invalid_argument`, use before fitting throws `std::logic_error`, and numeric overflow throws `std::overflow_error`.

## Core clustering operations

### `CentroidInitializer` — `k_means/Centroid_initialization.hpp`

```cpp
CentroidInitializer initializer(3);       // random_device seed
CentroidInitializer repeatable(3, 42U);    // deterministic seed
auto centroids = repeatable.initialize(data);
```

The initializer selects `k` distinct rows from the data. `getK()` reads the cluster count; `setK(k)` changes it and validates that it is positive. `k` must not exceed the number of data rows. Data must be nonempty, rectangular, have at least one feature, and contain finite values. Invalid input throws `std::invalid_argument`.

### `DistanceCalculator` — `k_means/Distance_Calculation.hpp`

```cpp
const double d = DistanceCalculator::distance(a, b);
const double d2 = DistanceCalculator::squareddistance(a, b);
```

Both methods require equal-dimensional points and throw `std::invalid_argument` when dimensions differ. `distance` returns Euclidean distance; `squareddistance` returns its square and is suitable for nearest-centroid comparisons. The utility class cannot be instantiated.

### `ClusterAssignment` — `k_means/ClusterAssignment.hpp`

```cpp
std::vector<int> labels =
    ClusterAssignment::assignClusters(data, centroids);
```

Returns one zero-based centroid index per input point. Empty data/centroids, ragged points, non-finite values, or mismatched dimensions are invalid and throw `std::invalid_argument`. Equal distances resolve to the lower centroid index. The utility class cannot be instantiated.

### `handleEmptyClusters` — `k_means/EmptyCluster.hpp`

```cpp
handleEmptyClusters(data, centroids, labels);
```

This free function modifies centroids and labels in place. For every empty cluster it chooses the farthest point from a donor cluster that has at least two points, assigns that point to the empty cluster, and sets the empty centroid to the point. Inputs must have matching row/label counts, valid labels, and matching finite dimensions; there cannot be more clusters than points. Inconsistent input or inability to repopulate an empty cluster throws `std::invalid_argument`.

### `CentroidUpdater` — `k_means/Centroid_Update.hpp`

```cpp
auto updated = CentroidUpdater::update(data, labels, centroids);
```

Returns a new centroid dataset without modifying the inputs. Each nonempty cluster's centroid is its coordinate-wise mean. Empty clusters keep their corresponding old centroid. Empty inputs, label-count mismatch, out-of-range labels, ragged rows, non-finite values, or dimension mismatch throw `std::invalid_argument`. The utility class cannot be instantiated.

### `ConvergenceDetector` — `k_means/ConvergenceDetector.hpp`

```cpp
ConvergenceDetector stopWhenStable(1e-4, 300);
const bool stop = stopWhenStable.shouldStop(
    oldCentroids, newCentroids, oldLabels, newLabels, iteration);
```

The constructor takes a non-negative finite centroid movement tolerance and a maximum iteration count of at least 1. Defaults are `1e-4` and `300`. `centroidsConverged` returns true when all paired centroids move no farther than tolerance; differing centroid counts return false, while point dimension mismatch throws. `assignmentsConverged` checks vector equality. `shouldStop` returns true if the iteration number is greater than or equal to the maximum, or if centroids **or** assignments have converged. The caller controls whether its count starts at 0 or 1. Setters enforce the same value constraints as construction.

### `ClusterEvaluator` — `k_means/Cluster_Evaluator.hpp`

```cpp
const double inertia =
    ClusterEvaluator::computeInertia(data, labels, centroids);
```

Computes the sum of squared Euclidean distances from each point to the centroid identified by its label. Inputs must be nonempty, finite, rectangular, dimensionally consistent, and have one valid label per point. Invalid arguments throw `std::invalid_argument`; a result outside the representable `double` range throws `std::overflow_error`. Inertia is meaningful relative to the coordinates supplied: scaled-data inertia should not be interpreted as an original-unit quantity.

## Exceptions and validation

The module comments and implementation are the final authority for exact edge behavior. Across the public API, invalid shapes, indexes, labels, or parameter values generally throw standard exceptions rather than returning a partial clustering result. Handle exceptions at application boundaries and validate data before starting a clustering loop.
