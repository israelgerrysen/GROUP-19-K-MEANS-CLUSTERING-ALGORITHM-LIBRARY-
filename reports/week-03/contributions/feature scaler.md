# Week 03 Report

## Encapsulation
The `FeatureScaler` class keeps its data members `method_`, `offsets_`, `scales_`, and `fitted_` private. Public functions such as `fit()`, `transform()`, `fit_transform()`, `inverse_transform()`, and `is_fitted()` allow the scaler to be used without directly accessing those variables. The private functions `validate()` and `apply()` handle internal tasks. This keeps the data and the operations that use it together in one class.

## Inheritance
Inheritance is a C++ concept where a new class is created from an existing class. The new class, called the derived class, can reuse accessible data and functions from the base class and can add its own features. Inheritance can reduce repeated code and help represent relationships between classes. The `FeatureScaler` class does not inherit from another class, so inheritance is not used in this implementation.

## Polymorphism
Polymorphism allows the same interface to be used for different behaviours. In C++, runtime polymorphism is commonly implemented with virtual functions and overridden functions in derived classes. The `FeatureScaler` class does not declare virtual functions or overrides. Its `Method` enum selects Min-Max scaling or Standard scaling, but selecting an option with a condition is not, by itself, runtime polymorphism.

## Conclusion
The `FeatureScaler` class demonstrates encapsulation by keeping its data members private and providing public functions to work with the scaler. Inheritance and runtime polymorphism are not implemented in this class.

## 4. Class Layout Drawing

![Class Layout Diagram](./diagrams/featureScaler(week_3_progress).jpg)
