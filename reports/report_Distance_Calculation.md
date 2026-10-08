# Week X Progress Report

## Completed
- Implemented distance calculation (`calculateEuclideanDistance(p1, p2)` in `Distance_calculation1.cpp`, declared in `Distance_Calculation.hpp`). It returns the Euclidean distance between two points with any number of features.
- The function throws `std::invalid_argument` if the two points have different numbers of features. Two empty points return `0`.
- Wrote a test program (`testing_distance.cpp`) with 9 checks: known distances (3-4-5 triangle, 1D, 3D, negative coordinates, 10 dimensions), identical points, symmetry, empty points, and mismatched dimensions. All checks pass.
- [Add other work completed by the team this week.]

## In Progress
- [Add tasks still being worked on, e.g. using the distance function in cluster assignment.]

## Challenges/Blockers
- The function name was spelled differently in the header (`calculateEuclideanDistance`) and the `.cpp` (`calculateEuclidianDistance`). The code compiled but failed at link time with `undefined reference`. Fixed by correcting the spelling in the `.cpp`.
- Building the test failed with `No such file or directory` because the terminal was in the wrong folder. Fix: move into the folder that contains the files before compiling.

## Next Week
- Use the distance function in cluster assignment and consider a squared-distance version, since the square root is not needed when only comparing distances.
- [Add other planned tasks.]

## AI Use
- Tool: Claude (Anthropic)
- Purpose: Reviewing the distance code (found the function-name spelling mismatch), writing the test program, and diagnosing the build errors.
- Reason: To find and fix the errors faster and to speed up writing tests. The code was compiled, run and checked by the team before use.