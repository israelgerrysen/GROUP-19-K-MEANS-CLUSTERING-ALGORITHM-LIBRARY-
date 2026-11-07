# Week 1 Progress Report

## Completed
- Created the centroid update feature for the K-Means project.
- Added `CentroidUpdater::update`, which moves each centroid to the average of the data points assigned to its cluster.
- Added input checks for missing data or centroids, incorrect assignment counts, invalid cluster labels, different point sizes, and non-finite numbers such as infinity or NaN.
- Made empty clusters keep their previous centroid, so the calculation does not divide by zero.
- Created a test file with checks for averages, one-point clusters, empty clusters, different data shapes, unchanged inputs, and invalid input.

## In Progress
- The feature and its test cases are written. The files reviewed do not show further unfinished work.

## Challenges/Blockers
- Each data point must have a valid cluster number and the same number of features as the centroids.
- Empty clusters need special handling. This feature keeps their old centroid; a separate empty-cluster feature could choose another approach.

## Next Week
- Connect centroid updating with the cluster assignment step so K-Means can repeat both steps.
- Deciding how the project should handle empty clusters across the full algorithm.
- Building and running the project tests, then fix any issues they reveal.

## AI Use
- Tool: OpenAI.
- Purpose: Read the centroid update header, source, and test files and draft this report.
- Reason: To explain the work in simple language for a presentation.
