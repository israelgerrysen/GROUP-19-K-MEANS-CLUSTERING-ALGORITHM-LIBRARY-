# Algorithm and Module Workflow

The assignment brief calls out dataset loading, data preprocessing, feature scaling, centroid initialization, distance calculation, cluster assignment, centroid update, convergence detection, empty-cluster handling, and cluster evaluation. The public modules implement these as separate operations. The caller owns the orchestration and the order of operations.

## End-to-end flow

```text
CSV or in-memory matrix
        |
        v
DataLoader (optional) -> DataPreprocessor -> FeatureScaler
                                             |
                                             v
                                  CentroidInitializer
                                             |
                    +------------------------+----------------------+
                    |                                               |
                    v                                               |
             ClusterAssignment <--- DistanceCalculator              |
                    |                                               |
                    v                                               |
             handleEmptyClusters                                    |
                    |                                               |
                    v                                               |
              CentroidUpdater                                       |
                    |                                               |
                    v                                               |
       ConvergenceDetector: repeat or stop -------------------------+
                    |
                    v
    final labels + ClusterEvaluator (inertia)
```

The actual project example is in `examples/kmeans_example_utils.hpp`. It copies the input, imputes missing values with each column's median, scales by min-max scaling, initializes centroids from distinct observations, alternates assignment/empty-cluster repair/update, checks convergence, assigns labels against the final centroids, evaluates inertia, and inverse-transforms centroids for display.

## Module responsibilities

| Stage | Public header | Responsibility and behavior |
|---|---|---|
| Dataset loading | `k_means/DataLoader.hpp` | Reads a CSV with a header row. Can load all columns or a selected, ordered list of zero-based columns. Invalid numeric values become NaN so a preprocessing step can handle them. |
| Data preprocessing | `k_means/DataPreprocessor.hpp` | Mutates the supplied numeric matrix to drop a column, remove rows containing NaN, impute NaN with mean/median/mode, or append one-hot columns from one category value per row. |
| Feature scaling | `k_means/feature_scaler.hpp` | Fits per-feature MinMax or Standard (z-score) statistics, transforms data, and inverse-transforms values. Call `fit` before `transform`/`inverse_transform`; `fit_transform` does both. |
| Centroid initialization | `k_means/Centroid_initialization.hpp` | Selects `k` distinct data rows. A supplied seed makes the random selection repeatable. Invalid `k`, empty, ragged, or non-finite data throws. |
| Distance calculation | `k_means/Distance_Calculation.hpp` | Provides Euclidean and squared Euclidean distance for equal-dimension points. Squared distance avoids a square root when comparing candidates. |
| Cluster assignment | `k_means/ClusterAssignment.hpp` | Assigns each point to the closest centroid and returns one integer label per point. Ties go to the lowest centroid index. |
| Empty-cluster handling | `k_means/EmptyCluster.hpp` | Moves the farthest eligible point from a donor cluster with more than one point into each empty cluster, updating the chosen centroid and label. Throws if consistent repopulation is impossible. |
| Centroid update | `k_means/Centroid_Update.hpp` | Replaces each centroid with the arithmetic mean of the assigned points. Inputs are not modified. An empty cluster retains its previous centroid. |
| Convergence detection | `k_means/ConvergenceDetector.hpp` | Checks whether each centroid moved no farther than tolerance, whether labels are unchanged, or the iteration limit has been reached. |
| Cluster evaluation | `k_means/Cluster_Evaluator.hpp` | Computes inertia: the sum of squared Euclidean distances from every point to its assigned centroid. |

## One iteration in detail

1. **Assign:** for each point, compute squared distance to every centroid and select the nearest one. The label is the centroid's zero-based index.
2. **Repair empties:** if any label has no observations, move the farthest point that can be removed without emptying its donor cluster. The moved point becomes the new empty cluster's centroid.
3. **Update:** calculate the coordinate-wise arithmetic mean for each cluster. An empty cluster keeps the centroid it had on entry to this step.
4. **Stop check:** compare old and new centroid positions, compare labels from the prior iteration, and check the maximum iteration count. `shouldStop` returns true when either stability condition holds or the count is at least the configured maximum.
5. **Final result:** compute labels once more against the final centroids before computing inertia; otherwise labels could correspond to centroids from the previous iteration.

## Data and coordinate conventions

- A point is `std::vector<double>`; a dataset is a `std::vector` of points. Several classes define these aliases within their own class.
- Labels are zero-based `int` values in the range `[0, number_of_centroids)`.
- Input points and centroids must have consistent feature counts. The distance, assignment, update, empty-cluster, and evaluator routines validate relevant dimensions and label ranges.
- Preprocessing functions mutate their matrix argument. Scaling returns transformed copies and keeps fitted statistics inside the scaler.
- For consistent inference or inverse transformation, fit a scaler on training data once and reuse that fitted scaler for subsequent data with the same feature count.
