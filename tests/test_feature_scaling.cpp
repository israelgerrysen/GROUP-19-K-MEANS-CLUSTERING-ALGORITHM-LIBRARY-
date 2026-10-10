#include "feature_scaler.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
int checks = 0;

void require(bool condition, const std::string& message) {
    ++checks;
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void close(double actual, double expected) {
    require(std::abs(actual - expected) <= 1e-10 * (1.0 + std::abs(expected)),
            "Unexpected numeric result.");
}

template <typename Exception, typename Function>
void throws(Function action) {
    bool caught = false;
    try {
        action();
    } catch (const Exception&) {
        caught = true;
    }
    require(caught, "Expected exception was not thrown.");
}
}

int main() {
    try {
        using Matrix = FeatureScaler::Matrix;
        using Method = FeatureScaler::Method;
        const Matrix original{{-10, 100, 7}, {0, 200, 7}, {10, 300, 7}};
        FeatureScaler scaler;
        require(!scaler.is_fitted(), "New scaler must be unfitted.");
        throws<std::logic_error>([&] { (void)scaler.transform(original); });
        throws<std::logic_error>([&] { (void)scaler.inverse_transform(original); });
        const auto scaled = scaler.fit_transform(original);
        require(scaler.is_fitted(), "Fit did not update state.");
        for (std::size_t i = 0; i < original.size(); ++i) {
            close(scaled[i][0], static_cast<double>(i) / 2.0);
            close(scaled[i][1], static_cast<double>(i) / 2.0);
            close(scaled[i][2], 0.0);
        }
        const auto restored = scaler.inverse_transform(scaled);
        for (std::size_t i = 0; i < original.size(); ++i) {
            for (std::size_t j = 0; j < original[i].size(); ++j) {
                close(restored[i][j], original[i][j]);
            }
        }
        close(original[0][0], -10);
        close(scaler.transform({{20, 400, 8}})[0][0], 1.5);
        close(scaler.transform({{20, 400, 8}})[0][2], 1.0);

        FeatureScaler standard(Method::Standard);
        const auto z = standard.fit_transform({{1, 9}, {2, 9}, {3, 9}});
        close(z[0][0], -std::sqrt(1.5));
        close(z[1][0], 0);
        close(z[2][0], std::sqrt(1.5));
        for (const auto& row : z) close(row[1], 0);
        double mean = 0;
        double variance = 0;
        for (const auto& row : z) {
            mean += row[0] / 3.0;
            variance += row[0] * row[0] / 3.0;
        }
        close(mean, 0);
        close(variance, 1);
        const auto back = standard.inverse_transform(z);
        close(back[0][0], 1);
        close(back[2][0], 3);
        close(standard.transform({{4, 9}})[0][0], std::sqrt(6.0));
        close(standard.fit_transform({{42}})[0][0], 0);
        close(standard.inverse_transform({{0}})[0][0], 42);

        throws<std::invalid_argument>([&] { scaler.fit({}); });
        throws<std::invalid_argument>([&] { scaler.fit({{}}); });
        throws<std::invalid_argument>([&] { scaler.fit({{1, 2}, {3}}); });
        throws<std::invalid_argument>([&] { scaler.fit({{std::numeric_limits<double>::quiet_NaN()}}); });
        throws<std::invalid_argument>([&] { scaler.fit({{std::numeric_limits<double>::infinity()}}); });
        throws<std::invalid_argument>([&] { (void)scaler.transform({{1}}); });
        throws<std::invalid_argument>([&] { (void)scaler.transform({}); });
        throws<std::invalid_argument>([&] { (void)scaler.transform({{1, 2, 3}, {1}}); });
        throws<std::invalid_argument>([&] { (void)scaler.inverse_transform({{1}}); });
        throws<std::invalid_argument>([&] {
            (void)scaler.transform({{1, 2, std::numeric_limits<double>::infinity()}});
        });
        throws<std::invalid_argument>([] { FeatureScaler invalid(static_cast<Method>(99)); });
        close(scaler.transform(original)[2][0], 1);
        scaler.fit({{5}, {15}});
        close(scaler.transform({{10}})[0][0], 0.5);
        FeatureScaler tiny;
        tiny.fit({{0}, {1e-300}});
        throws<std::overflow_error>([&] { (void)tiny.transform({{1e300}}); });
        std::cout << "All " << checks << " checks passed.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Test failed: " << error.what() << '\n';
        return 1;
    }
}
