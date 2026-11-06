# BUSULWA GERRYSON ISRAEL 25/U/0826 BELE
# Week 1 Progress Report

## Completed
- Created the centroid initialization feature for the K-Means project.
- Added `CentroidInitializer`, which selects `k` different rows from the input data to use as the starting centroids.
- Added a random mode and a seeded mode. A seed makes the same input produce the same selection, which is useful for repeatable examples and tests.
- Added checks for invalid values of `k`, empty data, too many centroids, points with different numbers of features, and values that are not finite numbers.
- Added getter and setter methods to read and update `k`. The setter rejects values below 1.
- Created a test file to check invalid inputs, distinct selected points, repeatable results with the same seed, selecting all points, and updating `k`.

## In Progress
- No unfinished Week 1 work is shown in the three files reviewed. The feature and its checks are present.

## Challenges/Blockers
- The initializer needs valid input: the dataset must not be empty, `k` must be at least 1 and no greater than the number of points, and every point must have the same number of finite feature values.
- No other blocker is shown in the files reviewed.

## Next Week
- Connect the initializer to the rest of the K-Means algorithm so its chosen points can be used as starting centroids.
- Build and run the project tests, then fix any issues they reveal.
- Review the feature with the group and agree on any improvements needed.

## AI Use
- Tool: OpenAI.
- Purpose: Read the Week 1 source files and draft this report in simple language.
- Reason: To  explain and understand the completed feature and its checks clearly.

## References
- Forgy, E. W. (1965). Cluster analysis of multivariate data: efficiency versus interpretability of classifications. Biometrics, 21(3), 768-769. (The source of picking random data points as starting centroids.)
- Hastie, T., Tibshirani, R., & Friedman, J. (2009). The Elements of Statistical Learning (2nd ed.). Springer. (The K-Means section is in chapter 14.)
