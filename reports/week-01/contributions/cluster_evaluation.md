# Week 1 Report

## Completed
- Implemented the foundational `Point` data structure to represent 2D coordinates efficiently.
- Developed the `calculateSquaredDistance` helper function to measure the Euclidean distance between data points and cluster centroids.
- Created the `computeInertia` function to calculate the total Within-Cluster Sum of Squares (WCSS) for model evaluation.
- Set up a test routine in `Cluster_evaluation.cpp` to simulate K-Means assignment and validate inertia using predefined "good" and "bad" centroid scenarios.
- Organized the code by splitting definitions into a header file (`Cluster_Evaluator.hpp`).

## In Progress
- Building the complete, iterative K-Means algorithm (currently only the assignment step and inertia evaluation are finished).
- Transitioning the current procedural approach (using standalone helper functions) into a more cohesive Object-Oriented class structure.

## Challenges/Blockers
- Managing boundary checks and vector bounds when mapping data points to dynamically assigned cluster labels.
- Resolving minor syntax and capitalization inconsistencies in the initial drafts of the C++ code to ensure smooth compilation.

## Next Week
- Testing using real world data to ensure all the functions properly function on real datasets.

## AI Use
- Tool: Gemini
- Purpose: help in the definition and understanding of the logic for the cluster evaluation.
- Reason: To ensure proper understanding of the logic under cluster evaluation.