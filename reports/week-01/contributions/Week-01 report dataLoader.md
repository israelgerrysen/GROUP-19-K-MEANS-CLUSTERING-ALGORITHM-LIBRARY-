# Progress Report: Project Structure and Data Loading

## Aim

Set up the project structure, then move data loading out of `k_means.cpp` into its own class. Clustering is not part of this stage.

## What was done

- **Folder structure:** `include/k_means/DataLoader.hpp` (header), `src/DataLoader.cpp` (implementation), `examples/example_load.cpp` (small program that calls the loader). `football.csv` and the old `k_means.cpp` are still in the root.
- **Loader:** `DataLoader::loadCSV(filename)` returns a `vector<vector<double>>`. It reads the file line by line, splits each line on commas, and converts each cell with `std::stod`. Cells that are not numbers (header, team names, dates) are skipped.
- **Error handling:** if the file cannot be opened, it throws a `runtime_error` with the filename. The first version reported a successful load of 0 rows in that case.

## Open issues

- Quoted fields like `"3,83"` are still split into two cells, and `stod` can accept one half as a stray number.
- Skipped text and empty cells make row widths uneven, so columns cannot yet be trusted by index.
- No tests and no CMake. The old `k_means.cpp` is still in the project.

## Next steps

- Fix the splitting so quoted fields stay in one cell.
- Choose the numeric features and normalise them.
- Add a small test (row count, column count, one quoted field) and a CMake file.
- Start the k-means implementation.
