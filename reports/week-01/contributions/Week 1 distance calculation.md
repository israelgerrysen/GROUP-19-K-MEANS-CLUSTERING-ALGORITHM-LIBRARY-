# SEBBOWA MASAMBILA ABRAHAM 25/U/04087/PS

# Week 1 Progress Report

## Completed
- Created the distance calculation feature for the K-Means project.
- Added `DistanceCalculator::distance`, which finds the Euclidean distance between two points.
- Added `DistanceCalculator::squareddistance`, which finds the squared distance without calculating a square root. This is useful when comparing distances to find the nearest centroid.
- Added checks that the two points have the same number of values and that their values are finite numbers.
- Created tests for common distance examples, points with different numbers of dimensions, and invalid values.

## In Progress
- The feature and its test cases are present in the files reviewed. The files do not show other unfinished work.

## Challenges/Blockers
- Both points must have the same number of dimensions. Otherwise, the calculation throws `std::invalid_argument`.
- Infinite and NaN values are rejected so they do not produce invalid distance results.
- The test file contains checks, but I have not confirmed from these files alone that the tests were run.

## Next Week
- Connect the distance functions to the step that finds the nearest centroid.
- Build and run the project tests, then fix any issues they reveal.
- Demonstrate how the normal and squared distance functions give useful results.

## AI Use
- Tool: OpenAI Codex.
- Reason: To explain the feature in simple language for a presentation.
