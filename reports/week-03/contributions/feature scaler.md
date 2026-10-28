# Week 03 Project Report

## Project: Feature Scaler

### 1. Encapsulation
The `FeatureScaler` class groups the data and functions needed for feature scaling. Its private members—`method_`, `offsets_`, `scales_`, and `fitted_`—store the selected method, scaling values, and fitted status. Public functions such as `fit()`, `transform()`, and `is_fitted()` allow users to work with the scaler without directly changing these private members. The private functions `validate()` and `apply()` support internal operations.

### 2. Inheritance
The `FeatureScaler` class does not inherit from another class in the supplied `feature_scaler.hpp` file. Therefore, inheritance is not demonstrated in this class.

### 3. Polymorphism
The supplied `feature_scaler.hpp` file does not declare virtual functions or overridden functions, so it does not demonstrate runtime polymorphism. The `Method` enum allows the implementation to choose Min-Max scaling or Standard scaling, but choosing an algorithm with a condition is not, by itself, runtime polymorphism.

## Conclusion
The `FeatureScaler` class clearly demonstrates encapsulation through private data members and public member functions. Inheritance and runtime polymorphism are not shown in the supplied header and implementation.

## 4. Class Layout Drawing

![Class Layout Diagram](./diagrams/featureScaler(week_3_progress).jpg)
