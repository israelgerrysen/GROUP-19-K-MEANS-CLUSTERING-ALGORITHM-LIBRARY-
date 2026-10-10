#include "feature_scaler.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

FeatureScaler::FeatureScaler(Method method) : method_(method) {
    if (method != Method::MinMax && method != Method::Standard) {
        throw std::invalid_argument("Unknown scaling method.");
    }
}

void FeatureScaler::validate(const Matrix& data) {
    if (data.empty() || data.front().empty()) {
        throw std::invalid_argument("Data must contain rows and features.");
    }
    const auto columns = data.front().size();
    for (const auto& row : data) {
        if (row.size() != columns) {
            throw std::invalid_argument("All rows must have the same number of features.");
        }
        for (double value : row) {
            if (!std::isfinite(value)) {
                throw std::invalid_argument("Features must be finite numbers.");
            }
        }
    }
}

void FeatureScaler::fit(const Matrix& data) {
    validate(data);
    const auto columns = data.front().size();
    std::vector<long double> offsets(columns);
    std::vector<long double> scales(columns);
    for (std::size_t j = 0; j < columns; ++j) {
        if (method_ == Method::MinMax) {
            long double minimum = data.front()[j];
            long double maximum = minimum;
            for (const auto& row : data) {
                minimum = std::min(minimum, static_cast<long double>(row[j]));
                maximum = std::max(maximum, static_cast<long double>(row[j]));
            }
            offsets[j] = minimum;
            scales[j] = maximum - minimum;
        } else {
            long double mean = 0.0L;
            std::size_t count = 0;
            for (const auto& row : data) {
                ++count;
                mean += (static_cast<long double>(row[j]) - mean) /
                        static_cast<long double>(count);
            }
            long double variance = 0.0L;
            count = 0;
            for (const auto& row : data) {
                ++count;
                const long double difference = static_cast<long double>(row[j]) - mean;
                const long double squared = difference * difference;
                variance += (squared - variance) / static_cast<long double>(count);
            }
            offsets[j] = mean;
            scales[j] = std::sqrt(variance);
        }
        if (!std::isfinite(offsets[j]) || !std::isfinite(scales[j])) {
            throw std::overflow_error("Scaling statistics exceed numeric limits.");
        }
        if (scales[j] == 0.0L) {
            scales[j] = 1.0L;
        }
    }
    offsets_ = std::move(offsets);
    scales_ = std::move(scales);
    fitted_ = true;
}

FeatureScaler::Matrix FeatureScaler::apply(const Matrix& data, bool inverse) const {
    if (!fitted_) {
        throw std::logic_error("Call fit before transforming data.");
    }
    validate(data);
    if (data.front().size() != offsets_.size()) {
        throw std::invalid_argument("Feature count differs from the fitted data.");
    }
    Matrix result = data;
    for (auto& row : result) {
        for (std::size_t j = 0; j < row.size(); ++j) {
            const long double value = inverse
                ? static_cast<long double>(row[j]) * scales_[j] + offsets_[j]
                : (static_cast<long double>(row[j]) - offsets_[j]) / scales_[j];
            if (!std::isfinite(value) ||
                std::abs(value) > std::numeric_limits<double>::max()) {
                throw std::overflow_error("Transformed value exceeds double precision range.");
            }
            row[j] = static_cast<double>(value);
        }
    }
    return result;
}

FeatureScaler::Matrix FeatureScaler::transform(const Matrix& data) const {
    return apply(data, false);
}

FeatureScaler::Matrix FeatureScaler::fit_transform(const Matrix& data) {
    fit(data);
    return transform(data);
}

FeatureScaler::Matrix FeatureScaler::inverse_transform(const Matrix& data) const {
    return apply(data, true);
}

bool FeatureScaler::is_fitted() const noexcept {
    return fitted_;
}
