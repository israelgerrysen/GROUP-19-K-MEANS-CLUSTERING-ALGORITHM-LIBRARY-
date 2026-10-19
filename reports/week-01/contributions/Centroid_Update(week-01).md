# Week 1 Progress Report

## Completed
- Wrote the `CentroidUpdater` class (`Centroid_Update.hpp` and `Centroid_Update.cpp`). It moves each centroid to the average of the points assigned to it.
- Made the class a utility class: one static function `update()` and a deleted constructor, so no object is needed.
- Added input checks that throw `std::invalid_argument` for empty data, empty centroids, wrong number of labels, labels out of range, and mismatched dimensions.
- Made empty clusters keep their old centroid instead of dividing by zero.
- Wrote the test file `testing_Centroid_Update.cpp` with 17 checks. All 17 pass.
- Added comments to the header, the implementation and the test file to explain the code.

## In Progress
- Connecting `CentroidUpdater` with the other modules (`ClusterAssignment`, `CentroidInitializer`, `DistanceCalculator`) so they work together in the K-Means loop.
- Deciding how empty clusters should be fixed. The header says this will be the job of an `EmptyClusterHandler`.

## Challenges/Blockers
- The project folder name has a space (`CPP PROJECT`), so the compile command failed until the file paths were put in quotes.
- The compiler could not find `Centroid_Update.hpp` because the header was in a different folder from the `.cpp` files. This was fixed with the `-I` option.
- After a failed compile, running `.\testing.exe` ran an old build and printed "All tests passed". I learned to run the test only when the compile succeeds.

## Next Week
- Combine the modules into one full K-Means loop (assign, update, repeat until the clusters stop changing).
- Write the `EmptyClusterHandler` for empty clusters.
- Test the full program on a small example dataset.

## AI Use
- Tool: Claude (by Anthropic)
- Purpose: Help with the compile commands and errors, add explanatory comments to my code, and give feedback on my report writing.
- Reason: To understand the errors faster and to make my code easier to read. I checked the results by compiling and running the tests myself.
