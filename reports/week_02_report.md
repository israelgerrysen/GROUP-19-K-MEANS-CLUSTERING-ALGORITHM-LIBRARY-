# week_02_Progress Report

**Project:** Design and Implementation of the K-Means Clustering Algorithm in C++  
**Component:** Feature Scaling  
**Report date:** 9 October 2026  

## Completed

- Implemented a reusable `FeatureScaler` class, with its declaration in `feature_scaler.hpp` and member-function definitions in `feature_scaler.cpp`.
- Implemented min-max scaling and standardization independently for each feature. Min-max scaling subtracts the fitted minimum and divides by the range. Standardization subtracts the mean and divides by the population standard deviation, calculated using denominator `n` [1, 2].
- Added parameter reuse, inverse transformation, input validation, and error handling.
- Created `test_feature_scaling.cpp`, `example_feature_scaling.cpp`, and `feature_scaling.md`.
- Compiled the test and example separately using GCC 13.3.0 with `-std=c++23 -Wall -Wextra -Wpedantic -Werror`. Both compiled without warnings and ran successfully in the development environment.
- Verified **52 automated checks**, covering expected scaling results, constant columns, single-observation data, inverse transformation, reuse of parameters, extrapolation, invalid inputs, refitting, preservation after rejected fitting, and output overflow. Floating-point comparisons use a tolerance.

### Class organization

**Class created and reason:** `FeatureScaler` keeps the selected method, fitted parameters, and operations together. An object can fit once and reuse its parameters for later observations. Rows represent observations and columns represent numeric features.

**Data members:** all four are private.

| Member | Type | Purpose |
| --- | --- | --- |
| `method_` | `Method` | Stores the selected scaling method |
| `fitted_` | `bool` | Initially false; records whether fitting has succeeded |
| `offsets_` | `std::vector<long double>` | Stores each feature's fitted minimum or mean |
| `scales_` | `std::vector<long double>` | Stores each feature's fitted range or population standard deviation; uses 1 for a zero divisor |

The object stores fitted parameters rather than the original dataset. `Matrix` is a public alias for `std::vector<std::vector<double>>`. `Method` is a public enumeration containing `MinMax` and `Standard`. Neither is an additional project class or a data member.

**Member functions and access:**

| Member function | Access | Purpose |
| --- | --- | --- |
| `FeatureScaler(Method method = Method::MinMax)` | Public | Constructor; selects and validates the method |
| `fit(const Matrix& data)` | Public | Calculates and stores the parameters |
| `transform(const Matrix& data) const` | Public | Returns scaled data using fitted parameters |
| `fit_transform(const Matrix& data)` | Public | Fits parameters, then transforms data |
| `inverse_transform(const Matrix& data) const` | Public | Returns scaled values to original units |
| `is_fitted() const noexcept` | Public | Reports fitted state |
| `validate(const Matrix& data)` | Private, static | Checks matrix shape and finite input values |
| `apply(const Matrix& data, bool inverse) const` | Private | Performs the shared forward or inverse transformation |

**Why public and private:** public operations let the rest of the program request fitting and scaling. Private data prevent callers from directly changing the stored parameters into an inconsistent state. Private helper functions keep validation and shared calculations inside the class.

**How the class is used:** the example creates `minmax` and `standard` objects and calls their public functions. The test program creates objects through the same interface. Neither program defines another project class. Intended integration passes a preprocessed numeric matrix into the scaler and supplies the returned matrix to the K-means components. K-means uses squared distances to centroids, so observations and centroids must be represented consistently [3]. Integration has not yet been verified.

### Demonstration results

| Original age | Original annual income | Min-max age | Min-max income |
| --- | --- | --- | --- |
| 20 | 20,000 | 0.000000 | 0.000000 |
| 30 | 40,000 | 0.500000 | 0.500000 |
| 40 | 60,000 | 1.000000 | 1.000000 |

- Standardization produced approximately −1.224745, 0.000000, and 1.224745 in each column.
- The new observation `(35, 50000)` became `(0.750000, 0.750000)` using the existing min-max parameters.
- Inverse transformation recovered the original demonstration values to the displayed precision.

### References

1. Scikit-learn developers. *MinMaxScaler: API documentation*. https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html
2. Scikit-learn developers. *StandardScaler: API documentation*. https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.StandardScaler.html
3. Scikit-learn developers. *Clustering user guide: K-means*. https://scikit-learn.org/stable/modules/clustering.html#k-means

These are online technical documentation references supporting the mathematical definitions. Verification of the C++ implementation is recorded separately above.

## In Progress

- The feature-scaling component is complete and verified independently. Integration with the dataset loader and full K-means implementation is pending; no integrated run is reported.
- Confirmation of the shared matrix interface and evaluation using the actual project dataset remain outstanding.

## Challenges/Blockers

- **Constant features:** a feature with identical values has zero range and zero standard deviation, making direct division invalid. The implementation uses a divisor of 1 when the calculated divisor is zero. Fitted constant values therefore become zero. Tests for both methods passed.
- **Invalid input:** empty matrices, inconsistent row lengths, NaN, and infinity could cause invalid calculations. Validation now rejects these inputs with exceptions, and the corresponding checks passed.
- **Consistent scaling of new data:** refitting on each new observation would change the parameters. Separate `fit` and `transform` operations retain and reuse the original parameters; the new-observation checks passed.
- **Numerical limits:** exceptionally large results can exceed the supported output range. The implementation checks for overflow and raises an exception; the overflowing-transformation check passed.
- **Integration blocker:** the dataset-loading and clustering components have not been supplied for integration testing. Standalone test results do not establish that the complete K-means program works.

## Next Week

- Confirm the matrix interface with the group and connect the scaler to the loading and preprocessing components.
- Run the component using the project dataset after checking that the supplied features are numeric and suitable for scaling.
- Supply scaled observations consistently to centroid initialization, distance calculation, assignment, centroid updates, and convergence checks.
- Verify the integrated program and record actual results and any integration problems.
- Apply inverse transformation when reporting centroids in their original units.

## AI Use

- **Tool:** OpenAI ChatGPT.
- **Purpose:** Assisted with understanding the purpose, importance and implementation of feature scaling in the project.
- **Reason:** To support implementation and explanation of the feature-scaling component.