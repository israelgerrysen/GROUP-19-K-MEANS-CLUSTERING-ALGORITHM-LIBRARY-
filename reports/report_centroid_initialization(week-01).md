# Week-01 Progress Report

## Completed
- Implemented centroid initialization (`initializeCentroids(data, k)` in `Centroid_initialization.cpp`, declared in `Centroid_initialization.hpp`). It selects `k` unique random points from the dataset as the starting centroids, by shuffling the list of indices and taking the first `k`.
- Invalid input (empty dataset, `k <= 0`, or `k` larger than the dataset) returns an empty result.
- Wrote a test program (`testing_Centroid_intialization.cpp`) that checks the invalid cases, that exactly `k` centroids are returned, that they are unique, and that each one comes from the dataset. All checks pass.
- 

## In Progress
- Creation of a class called `CentroidInitializer` in the `Centroid_initialization.hpp` header file.

## Challenges/Blockers
- Linker error `undefined reference to initializeCentroids(...)` when building the test
- Cause: only the test file was compiled. 
- Fix: compiling the test file together with the implementation file
  `g++ -std=c++23 testing_Centroid_intialization.cpp Centroid_initialization.cpp -o test`
- The current version uses plain random selection, so results can vary between runs. A smarter method such as K-Means++ could be considered later.

## Next Week
- Integrating centroid initialization with the other modules of the K-Means library.


## AI Use
- Tool: Claude (Anthropic)
- Purpose: Explaining centroid initialization, simplifying the code, writing the test program, and diagnosing the linker error.
- Reason: To understand the algorithm and fix the build error faster. The code was compiled, run and checked by the team before use.

## References
- Forgy, E. W. (1965). Cluster analysis of multivariate data: efficiency versus interpretability of classifications. Biometrics, 21(3), 768-769. (The source of picking random data points as starting centroids.)
- Hastie, T., Tibshirani, R., & Friedman, J. (2009). The Elements of Statistical Learning (2nd ed.). Springer. (The K-Means section is in chapter 14.)