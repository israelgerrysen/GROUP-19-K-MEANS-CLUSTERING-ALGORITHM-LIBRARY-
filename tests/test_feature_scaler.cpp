#include "feature_scaler.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

bool close(double a, double b) { return std::abs(a - b) < 1e-9; }

int main() {
    using Matrix = FeatureScaler::Matrix;

    FeatureScaler minmax;
    assert(!minmax.is_fitted());
    Matrix input{{10, 100}, {20, 200}, {30, 300}};
    Matrix scaled = minmax.fit_transform(input);
    assert(minmax.is_fitted());
    assert(close(scaled[0][0], 0.0));
    assert(close(scaled[1][0], 0.5));
    assert(close(scaled[2][1], 1.0));
    assert(close(minmax.inverse_transform(scaled)[1][0], 20.0));
    assert(close(input[0][0], 10.0));

    FeatureScaler standard(FeatureScaler::Method::Standard);
    Matrix z = standard.fit_transform({{10}, {20}, {30}});
    assert(close(z[1][0], 0.0));
    assert(close(z[0][0], -std::sqrt(1.5)));
    assert(close(standard.inverse_transform(z)[2][0], 30.0));

    bool rejected = false;
    try { minmax.fit({}); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    std::cout << "All simple tests passed.\n";
}
