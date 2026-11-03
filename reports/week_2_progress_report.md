NAKAWEESA LINDA LUCY
25/U/02658/PS

# FeatureScaler: Class Structure and Implementation

## 1. What class did you create?

I created `FeatureScaler` (in `feature_scaler.hpp` and `feature_scaler.cpp`). It rescales the columns (features) of a data table so they are on a similar scale. It supports two methods, chosen with the `Method` enum:

- **MinMax** squeezes each feature into the range 0 to 1.
- **Standard** shifts each feature to a mean of 0 and a standard deviation of 1.

## 2. Why?

K-means groups points by distance. If one feature has big numbers (income, around 50,000) and another has small ones (age, around 30), the big one dominates and the small one is effectively ignored. Scaling gives every feature a fair influence.

I used a class because scaling needs memory. The numbers learned from the training data must be saved and reused to scale new data the same way and to convert results, such as cluster centers, back to the original units.

## 3. What data does it hold?

All of it is private:

- `method_` is the chosen scaling method.
- `offsets_` holds one number per feature: the minimum (MinMax) or the mean (Standard).
- `scales_` holds one number per feature: the range (MinMax) or the standard deviation (Standard).
- `fitted_` records whether `fit` has finished successfully.

A constant feature would have a scale of 0, so the class uses 1 instead to avoid dividing by zero.

## 4. What functions operate on that data?

**Public:**

- `FeatureScaler(method)` stores the method (default MinMax).
- `fit(data)` learns the offsets and scales.
- `transform(data)` scales data: `(value - offset) / scale`.
- `fit_transform(data)` does both in one call.
- `inverse_transform(data)` reverses the scaling: `value * scale + offset`.
- `is_fitted()` reports whether `fit` has been run.

**Private helpers:**

- `validate(data)` checks that the data is non-empty, rectangular, and finite.
- `apply(data, inverse)` does the math for both `transform` and `inverse_transform`, so the checks are written once.

## 5. Why are some members private and others public?
The **public** functions are the only actions other code needs: learn, scale, unscale, and check status. The **private** data cannot be changed by accident, since only `fit` sets it, and only after all calculations succeed. The private helpers are internal steps that can change without breaking other code.
 
 How is the class used?
 
Intended use in the k-means program :

1. `FeatureScaler scaler(FeatureScaler::Method::Standard);`
2. `auto scaled = scaler.fit_transform(data);`
3. Run k-means on `scaled`.
4. `scaler.inverse_transform(centroids);` to return results to the original units.

Calling `transform` before `fit` throws an error instead of returning wrong numbers.
