# Week 2 Progress Report

## Completed
- Refactored `DataLoader.cpp` to parse CSV files character-by-character, successfully resolving the issue of quoted fields with internal commas (e.g., `"3,83"`) splitting into multiple cells.
- Implemented error handling in the DataLoader to map empty cells or invalid non-numeric strings to `NaN`, guaranteeing consistent column widths across the entire matrix.
- Developed `test_dataloader.cpp` to programmatically verify row counts, column counts, and quoted string parsing.

## In Progress
- Developing a practical example using a real-world dataset to demonstrate the complete data loading process in action.

## Challenges/Blockers
- System environment restrictions and path recognition issues prevented the installation and configuration of CMake for automated project building.
- *Resolution:* Bypassed CMake entirely and executed direct `g++` compilation commands in the terminal to compile the library components and run the test.

## Next Week
- Working on the CMake file to ensure automated project building where library components are compiled automatically when running a program.

## AI Use
- Tool: Gemini
- Purpose: Helped in the explanation and understanding of the issue of fields with commas (e.g `"3,83"`).
- Reason: To ensure proper understanding of the nested comma issue so as to get a solution.

## Reference
- https://scikit-learn.org/stable/datasets/loading_other_datasets.html
