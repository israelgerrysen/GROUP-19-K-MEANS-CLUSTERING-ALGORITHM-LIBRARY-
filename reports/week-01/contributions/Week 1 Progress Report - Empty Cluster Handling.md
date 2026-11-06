# OKOBOI REUBEN 25/U/08779/PS
# BCCE

# Week 1 Progress Report

## Completed
- Created the empty cluster handling feature for the K-Means clustering project (`handleEmptyClusters`).
- Defined the API header in `EmptyCluster.hpp` using `#pragma once` header guards.
- Implemented `handleEmptyClusters` to repair empty clusters during algorithm execution by reassigning the farthest eligible point from a donor cluster (which must retain at least one point) and updating both assignments and target centroids directly.
- Implemented robust error checks and input validations:
  - Ensured `data` and `centroids` vectors are non-empty.
  - Verified that `assignments` vector size equals the number of data points.
  - Checked that the cluster count does not exceed the total number of data points (`centroids.size() <= data.size()`).
  - Guaranteed feature dimension consistency across all data points and centroids.
  - Verified coordinate values are finite numbers (rejecting `NaN` and `Infinity`).
  - Checked that all initial assignment labels fall strictly within valid centroid bounds (`0 <= label < centroids.size()`).
  - Threw `std::invalid_argument` if an empty cluster cannot be repopulated without reducing a donor cluster to size 0.

## In Progress
- The `handleEmptyClusters` function and header declaration are completed.
- Developing unit tests to verify edge cases, such as multiple empty clusters occurring simultaneously or instances where donor clusters cannot donate points.

## Challenges/Blockers
- Tracking donor cluster counts dynamically to guarantee no donor cluster is emptied during point transfer.
- Distinguishing between points already moved during a repair cycle using a tracking vector (`std::vector<bool> moved`) to prevent double reassignment.
- Ensuring that calculations for continuous squared distances between points and their original centroids handle edge boundaries correctly without numeric overflow.

## Next Week
- Integrate `handleEmptyClusters` directly after the cluster assignment step in the main K-Means loop.
- Build and execute unit tests covering boundary error conditions and cluster repopulation scenarios.
- Benchmark algorithm performance to ensure empty cluster recovery does not cause infinite looping or improper convergence.

## AI Use
- Tool: OpenAI Codex.
- Reasoning regarding state synchronization (updating labels, cluster counts, and centroids simultaneously) and boundary validation in C++ data structures.