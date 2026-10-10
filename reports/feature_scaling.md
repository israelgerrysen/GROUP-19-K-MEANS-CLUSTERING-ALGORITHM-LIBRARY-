# Feature Scaling for the C++ K-Means Project

## What feature scaling does

Feature scaling changes the numerical scale of each feature (column). Rows represent observations; columns represent numeric features. K-means minimizes squared distances from observations to their cluster centroids [3]. Because those distances include the numerical differences in every column, changing a column's scale changes its contribution to the clustering objective. Scaling should therefore reflect the intended importance of the features; it does not guarantee better clusters.

For example, age and income have different units and numerical ranges. In the example program, the difference between the first two customers is 10 years and 20,000 income units. Their squared Euclidean distance is 10² + 20,000² = 400,000,100. After min-max scaling, the difference is 0.5 in each column, giving 0.5² + 0.5² = 0.5. This is a worked example, not a real customer dataset.

## Implemented methods

### Min-max scaling

For feature j:

`scaled_value = (value - minimum_j) / (maximum_j - minimum_j)`

The nonconstant fitted columns map into [0, 1] [1]. The default method is min-max scaling. Values in later data can fall outside [0, 1] if they exceed the fitted range; this implementation does not clip them.

### Standardization

For feature j:

`mean_j = sum(values_j) / n`

`variance_j = sum((value - mean_j)^2) / n`

`standard_deviation_j = sqrt(variance_j)`

`scaled_value = (value - mean_j) / standard_deviation_j`

The denominator is n, not n - 1: this is population-variance scaling, consistent with StandardScaler's documented convention [2]. Nonconstant fitted columns have approximately zero mean and unit population variance, allowing for floating-point rounding. Standardization does not make a distribution normal.

### Constant columns

If a fitted column has zero range or zero standard deviation, its divisor is set to 1. Subtracting the fitted offset then gives zero for its fitted values. This avoids division by zero and retains the column count. A later different value in that column is transformed by subtracting its fitted offset; it is not automatically forced to zero.

## Files

| File | Purpose |
| --- | --- |
| feature_scaler.hpp | Class declaration, matrix type, scaling methods, and public interface |
| feature_scaler.cpp | Validation, parameter fitting, transformation, and inverse transformation |
| test_feature_scaling.cpp | Standalone automated test program |
| example_feature_scaling.cpp | Worked customer-feature demonstration |
| feature_scaling.md | Design, formulas, integration, and build instructions |
| week_report.md | Completed work and verified results |

## Class structure and implementation

### What class was created, and why?

The component defines one class, `FeatureScaler`. It groups the selected scaling method, fitted parameters, and functions that use those parameters into one object. This allows a program to fit once and reuse the same parameters for later observations.

The class is declared in `feature_scaler.hpp`. Its member functions are defined in `feature_scaler.cpp`. The example and test programs include the header and call the public functions. They do not define additional project classes.

`Matrix` is a public type alias for `std::vector<std::vector<double>>`; it is not a separate class created for this project. `Method` is a public enumeration with the choices `MinMax` and `Standard`; it is not a data member. The object stores the chosen enumeration value in `method_`.

### What data does the class hold?

All four data members are private:

| Data member | Exact type | Initial state and purpose |
| --- | --- | --- |
| `method_` | `Method` | Set by the constructor; selects min-max scaling or standardization |
| `fitted_` | `bool` | Initially `false`; becomes `true` after a successful fit |
| `offsets_` | `std::vector<long double>` | Initially empty; stores one fitted minimum or mean per feature |
| `scales_` | `std::vector<long double>` | Initially empty; stores one fitted range or population standard deviation per feature, using 1 for a zero divisor |

For min-max scaling, `offsets_[j]` contains the minimum of feature `j`, and `scales_[j]` contains its range. For standardization, they contain its mean and population standard deviation. The number of fitted features is obtained from `offsets_.size()`; no separate feature-count member is declared.

The object stores the fitted parameters, not the original dataset. Variables such as `mean`, `variance`, `minimum`, and `maximum` are local variables inside `fit`, not class data members.

### What functions operate on that data?

| Member | Access | Purpose and effect on the object |
| --- | --- | --- |
| `explicit FeatureScaler(Method method = Method::MinMax)` | Public | Constructor; stores and validates the selected method. With no argument, selects min-max scaling |
| `void fit(const Matrix& data)` | Public | Validates the data, computes offsets and divisors, stores them, and marks the object as fitted |
| `Matrix transform(const Matrix& data) const` | Public | Returns scaled data using the fitted parameters; does not change the object |
| `Matrix fit_transform(const Matrix& data)` | Public | Calls `fit`, then `transform`; changes the fitted parameters and returns scaled data |
| `Matrix inverse_transform(const Matrix& data) const` | Public | Returns values in original units using the fitted parameters; does not change the object |
| `bool is_fitted() const noexcept` | Public | Returns `fitted_` without changing the object or throwing an exception |
| `static void validate(const Matrix& data)` | Private | Checks matrix shape and finite input values; uses no object-specific data |
| `Matrix apply(const Matrix& data, bool inverse) const` | Private | Checks fitted state and feature count, then performs forward or inverse transformation without changing the object |

`transform` calls `apply(data, false)`, while `inverse_transform` calls `apply(data, true)`. Both therefore share validation and numeric-range checks. Forward transformation calculates `(value - offset) / scale`; inverse transformation calculates `value * scale + offset`.

The `const Matrix&` parameters allow functions to read the supplied matrix without making a parameter copy or modifying it. The `const` after a member-function declaration means that the function does not change the object's state. `[[nodiscard]]` marks returned results that callers should use. These declarations are visible in the header.

### Why are some members private and others public?

The fitted parameters and state are private so that calling code cannot directly change them into an inconsistent combination. For example, changing the offsets without changing the corresponding divisors would make the transformation incorrect. The private helpers keep validation and shared transformation logic inside the class.

The constructor and the five public operations form the interface that the rest of the program needs. `Matrix` and `Method` are public so callers can name the input type and choose a scaling method. This separation is how this implementation applies encapsulation: calling code requests an operation, and the object manages its own parameters.

### How is the class used by the rest of the program?

In `example_feature_scaling.cpp`, `main` creates two objects: `minmax` and `standard`. Each object holds its own fitted parameters. The example calls `fit_transform` for the demonstration dataset, then uses `minmax.transform` for a new customer and `minmax.inverse_transform` to recover the original values. The standalone `print_data` function displays matrices; it is not a member of `FeatureScaler`.

The following complete example shows the interface in use:

```cpp
#include "feature_scaler.hpp"

int main() {
    const FeatureScaler::Matrix data{
        {20.0, 20000.0},
        {30.0, 40000.0},
        {40.0, 60000.0}
    };
    FeatureScaler scaler(FeatureScaler::Method::MinMax);
    const auto scaled = scaler.fit_transform(data);
    const auto new_scaled = scaler.transform({{35.0, 50000.0}});
    const auto restored = scaler.inverse_transform(scaled);
    return scaler.is_fitted() && !new_scaled.empty() && !restored.empty()
        ? 0 : 1;
}
```

In `test_feature_scaling.cpp`, objects are created and exercised through this same public interface. The standalone helpers `require`, `close`, and `throws` check results and exceptions; they are not class members.

For integration, the loading and preprocessing components supply a numeric matrix. A `FeatureScaler` object returns the scaled matrix for the K-means components. Observations and centroids must use the same fitted coordinate system. This is the intended integration; the other components have not yet been supplied or tested with this module.

The class uses composition through its vector data members. It does not declare inheritance, virtual functions, or derived classes because the current component does not require them.

## Using the scaler

```cpp
#include "feature_scaler.hpp"

FeatureScaler::Matrix data{{20, 20000}, {30, 40000}, {40, 60000}};
FeatureScaler scaler(FeatureScaler::Method::MinMax);
auto scaled_data = scaler.fit_transform(data);
auto scaled_new_data = scaler.transform({{35, 50000}});
```

Use scaled_data for centroid initialization, distance calculations, assignment, centroid updates, and convergence checks. Keep observations and centroids in the same scaled coordinate system. The component responsible for loading and preprocessing must supply the numeric matrix. CSV parsing, missing-value imputation, and categorical encoding belong outside this module. Exclude identifiers and outcome labels from the feature matrix.

For held-out evaluation or prediction, fit only on the training observations and transform later observations with those parameters. The demonstration follows that pattern for the new customer. If there is no held-out split and clustering is purely descriptive, fit on the dataset being clustered.

## Input validation and numerical limits

- Reject empty datasets, zero-column rows, and inconsistent row lengths.
- Reject NaN and infinite inputs.
- Reject transformation before fitting and mismatched feature counts.
- Reject invalid scaling-method enum values.
- Throw an overflow exception if fitted statistics or transformed results exceed the supported numeric range.

Statistics use long double intermediates; results use double. Standardization uses an incremental mean and a second pass for population variance. Floating-point precision and the range of long double depend on the compiler and platform; exceptionally extreme datasets can still raise an overflow error. Very small nonzero scales are retained rather than treated as constant.


## Verified example output

| Original age | Original income | Scaled age | Scaled income |
| --- | --- | --- | --- |
| 20 | 20000 | 0.000000 | 0.000000 |
| 30 | 40000 | 0.500000 | 0.500000 |
| 40 | 60000 | 1.000000 | 1.000000 |

For standardization, both columns produce -1.224745, 0.000000, and 1.224745. The new customer (35, 50000) maps to (0.750000, 0.750000) using the fitted min-max parameters.


## References

1. Scikit-learn developers. MinMaxScaler API documentation. https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html
2. Scikit-learn developers. StandardScaler API documentation. https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.StandardScaler.html
3. Scikit-learn developers. Clustering user guide, K-means. https://scikit-learn.org/stable/modules/clustering.html#k-means
