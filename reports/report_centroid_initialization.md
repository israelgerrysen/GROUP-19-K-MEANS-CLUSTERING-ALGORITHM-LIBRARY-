# Week X Progress Report

## Completed
- Implemented centroid initialization (`initializeCentroids(data, k)` in `Centroid_initialization.cpp`, declared in `Centroid_initialization.hpp`). It selects `k` unique random points from the dataset as the starting centroids, by shuffling the list of indices and taking the first `k`.
- Invalid input (empty dataset, `k <= 0`, or `k` larger than the dataset) returns an empty result.
- Wrote a test program (`testing_Centroid_intialization.cpp`) that checks the invalid cases, that exactly `k` centroids are returned, that they are unique, and that each one comes from the dataset. All checks pass.
- [Add other work completed by the team this week.]

## In Progress
- [Add tasks still being worked on, e.g. integrating initialization with the distance and cluster assignment modules.]

## Challenges/Blockers
- Linker error `undefined reference to initializeCentroids(...)` when building the test. Cause: only the test file was compiled. Fix: compile the test file together with the implementation file:
  `g++ -std=c++23 testing_Centroid_intialization.cpp Centroid_initialization.cpp -o test`
- The current version uses plain random selection, so results can vary between runs. A smarter method such as K-Means++ could be considered later.

## Next Week
- Integrate centroid initialization with the other modules of the K-Means library.
- [Add other planned tasks.]

## AI Use
- Tool: Claude (Anthropic)
- Purpose: Explaining centroid initialization, simplifying the code, writing the test program, and diagnosing the linker error.
- Reason: To understand the algorithm and fix the build error faster. The code was compiled, run and checked by the team before use.