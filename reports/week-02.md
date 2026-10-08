# Week 2 Progress Report

## Completed
- Implemented the `DataPreprocessor.hpp` and `DataPreprocessor.cpp` modules to clean and prepare matrices for the K-Means algorithm.
- Created `dropColumn` and `dropRowsWithMissingData` functions to handle unneeded or heavily corrupted data points.
- Developed robust statistical imputation methods (`fillMissingWithMean`, `fillMissingWithMedian`, `fillMissingWithMode`) to safely replace `NaN` values without discarding entire rows.
- Built a `oneHotEncode` method to dynamically translate categorical strings into binary numerical columns.
- Authored a standalone C++ test script (`test_preprocessing.cpp`) and verified all matrix manipulation logic successfully.

## In Progress
- Developing a practical example using a real-world dataset to demonstrate the complete data loading and preprocessing pipeline in action.

## Challenges/Blockers
- System environment restrictions and path recognition issues prevented the installation and configuration of CMake for automated project building.
- *Resolution:* Bypassed CMake entirely and executed direct `g++` compilation commands in the terminal to compile the library components and run the test suite.

## Next Week
- Finalize and test the Feature Scaling implementation.
- Begin building the core K-Means algorithm classes, starting with random centroid initialization and Euclidean distance calculations.

## AI Use
- Tool: Gemini
- Purpose: C++ implementation logic for the statistical imputation functions and providing exact `g++` terminal commands for manual compilation.
- Reason: To ensure complex edge cases (such as dividing by zero in empty columns) were safely handled in the C++ logic, and to establish an immediate workaround for the CMake configuration blocker.