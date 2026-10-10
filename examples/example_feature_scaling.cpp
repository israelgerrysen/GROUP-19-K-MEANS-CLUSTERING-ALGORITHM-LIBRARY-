#include "feature_scaler.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string_view>

void print_data(std::string_view title, const FeatureScaler::Matrix& data) {
    std::cout << '\n' << title << "\nAge\tAnnual income\n";
    for (const auto& row : data) {
        std::cout << row[0] << '\t' << row[1] << '\n';
    }
}

int main() {
    try {
        const FeatureScaler::Matrix customers{
            {20.0, 20000.0}, {30.0, 40000.0}, {40.0, 60000.0}
        };
        std::cout << std::fixed << std::setprecision(6);
        print_data("Original customer features", customers);

        FeatureScaler minmax(FeatureScaler::Method::MinMax);
        const auto scaled = minmax.fit_transform(customers);
        print_data("Min-max scaled features", scaled);

        FeatureScaler standard(FeatureScaler::Method::Standard);
        print_data("Standardized features", standard.fit_transform(customers));

        const FeatureScaler::Matrix new_customer{{35.0, 50000.0}};
        print_data("New customer using fitted min-max parameters",
                   minmax.transform(new_customer));
        print_data("Recovered original features", minmax.inverse_transform(scaled));
        std::cout << "\nPass the scaled matrix to the K-means component.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
