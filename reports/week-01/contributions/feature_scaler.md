NAKAWEESA LINDA LUCY
(25/U/02658/PS)
# Week 1 Progress Report

## Completed
- Built a **FeatureScaler**: a tool that puts all features on a similar scale before k-means runs
- Added two scaling options:
  - **MinMax:** squeezes each feature into a 0 to 1 range
  - **Standard:** centres each feature around 0 with a spread of 1
- Made it **reusable**: learn the scaling from training data (`fit`), apply it to new data (`transform`), and undo it (`inverse_transform`)
- Added **safety checks** for bad input: empty data, uneven rows, NaN/infinite values, wrong number of features, and using the scaler before fitting it
- Handled **constant features** (every value the same) so the code never divides by zero

## In Progress
- Writing unit tests for the tricky cases (constant column, single row, bad input)
- Writing clear documentation in the header file

## Challenges/Blockers
- **Which standard deviation to use:** I used the population version (divide by n). Need to document this choice
- **Very tiny variation:** a feature that barely changes could still cause huge numbers after scaling
- **Error timing:** `fit_transform` can finish fitting and then fail on extreme data

## Next Week
- Finish and run the tests
- Add the header documentation
- Plug FeatureScaler into the k-means pipeline and compare results with and without scaling

## AI Use
- Tool: Claude
- Purpose: Reviewed my code for errors and missing edge cases, suggested tests
           Helped me understand compilation errors and review the header, CPP and test files.
         



