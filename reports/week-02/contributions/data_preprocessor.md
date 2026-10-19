# Week 2 Report
# SSEGAWA JASIFA
# 25/U/08782/PS
# BCCE

# Class Structure and Implementation: Data Preprocessing

## 1. What class did you create?
I created the `DataPreprocessor` class.

## 2. Why?
This class was created to handle the data cleaning and formatting tasks required before passing a dataset to an algorithm. It provides standardized, reusable methods for removing irrelevant data, handling missing values, and converting categorical strings into a numerical format, ensuring the dataset is ready for mathematical processing.

## 3. What data does it hold?
The `DataPreprocessor` class does not hold any data members. It functions strictly as a utility class, operating directly on the external datasets passed into its methods via a 2D vector `std::vector<std::vector<double>>& dataset`.

## 4. What functions operate on that data?
The class contains several static member functions designed to manipulate and clean the provided dataset:
*   **`dropColumn`**: Removes a specific, irrelevant, or redundant column from the dataset.
*   **`dropRowsWithMissingData`**: Deletes any rows that contain missing (`NaN`) values to clean incomplete data.
*   **`fillMissingWithMean`**: Calculates the mean of a column and replaces any missing values with that average.
*   **`fillMissingWithMedian`**: Replaces missing values with the median of the column, which is useful for reducing the influence of outliers.
*   **`fillMissingWithMode`**: Finds the most frequently occurring value in a column and uses it to replace missing data.
*   **`oneHotEncode`**: Converts categorical string data into a numerical format by appending binary columns representing unique categories.

## 5. Why are some members private and others public? How is the class used by the rest of the program?
**Public vs. Private:** In the `DataPreprocessor` class, all member functions are `public`, and there are no `private` members. Because it is a static utility class with no internal state or data members to protect, there is no need for encapsulation. Every function is designed to be accessible globally to perform operations on external datasets.

**Usage by the Program:** The rest of the program uses this class without needing to create an instance of it. The functions are called directly using the class name e.g., `DataPreprocessor::fillMissingWithMean(dataset)`. It serves as the data preparation pipeline taking the raw dataset, cleaning and formatting it through these static methods, and then passing the refined data off to the main clustering algorithms.
