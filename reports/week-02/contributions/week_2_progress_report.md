# Week 2 Progress Report

## 1. What class did you create?
I created a class called `FeatureScaler` in C++.

## 2. Why?
I created it to scale numerical data using MinMax scaling or Standard scaling.

## 3. What data does it hold?
The class stores the scaling method (`method_`), the values used for scaling (`offsets_` and `scales_`), and a flag (`fitted_`) to show whether it has been fitted.

## 4. What functions operate on that data?
`fit()` calculates the scaling values. `transform()` scales the data, `fit_transform()` fits and scales it, and `inverse_transform()` changes it back. `is_fitted()` checks if fitting has been done. The private `validate()` and `apply()` functions help check and process the data.

## 5. Why are some members private and others public?
The public functions allow other parts of the program to use the scaler. The private members keep the scaling values from being changed directly.

## 6. How is the class used by the rest of the program?
In the test program, I create a `FeatureScaler` object, give it data, and check the results.
