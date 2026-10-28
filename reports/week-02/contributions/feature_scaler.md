# Week 2 Progress Report

1. What class did you create?

I created a C++ class called `FeatureScaler`. The class is designed to organize the data and functions needed to scale numerical data. 

2. Why?

I created the `FeatureScaler` class to scale numerical data using MinMax scaling or Standard scaling. MinMax scaling adjusts values based on the minimum and maximum values in the data, while Standard scaling uses the data's central value and variation to transform the values. Scaling can help put features with different ranges on a more comparable scale, which is useful in data processing and machine-learning tasks.

3. What data does it hold?

The class stores the selected scaling method in `method_`. It stores the values needed to perform the transformation in `offsets_` and `scales_`. It also has a Boolean flag called `fitted_`, which indicates whether the class has already been fitted to data. 
4. What functions operate on that data?

The `fit()` function examines the input data and calculates the values needed for scaling. The `transform()` function uses the calculated values to scale data, while `fit_transform()` combines fitting and transformation in one operation. The `inverse_transform()` function converts scaled data back toward its original values using the stored scaling information. The `is_fitted()` function checks whether fitting has been completed. The private `validate()` function checks whether the input data is suitable for processing, while the private `apply()` function performs the main transformation or inverse-transformation calculations.

5. Why are some members private and others public?

The public functions are available to other parts of the program, allowing users to fit the scaler, transform data, restore transformed data, and check its fitted status. The private members store the internal state and scaling values, while the private helper functions carry out internal tasks. This design prevents the scaling values from being changed directly by outside code and makes the class easier and safer to use. It is an example of encapsulation in C++.

6. How is the class used by the rest of the program?

In the test program, I create a `FeatureScaler` object and provide it with numerical data. The object is fitted to the data to calculate the required scaling values, and the transformation functions are then used to scale the data. The test program can check the output to see whether the scaling works as expected. It can also use `inverse_transform()` to convert scaled values back toward their original values and `is_fitted()` to check whether fitting has taken place.
