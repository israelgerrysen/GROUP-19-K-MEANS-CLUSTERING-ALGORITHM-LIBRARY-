// Stateful feature-scaling API. Fit statistics on training data, then reuse them
// to transform new rows or invert transformed values.
#ifndef FEATURE_SCALER_HPP
#define FEATURE_SCALER_HPP

#include <cstddef>
#include <vector>

class FeatureScaler {
public:
    using Matrix = std::vector<std::vector<double>>;

    enum class Method {
        MinMax,
        Standard,
        Standardization = Standard
    };

    // Choose MinMax (range scaling) or Standard (zero mean, unit variance).
    explicit FeatureScaler(Method method = Method::MinMax);

    // Learn per-feature statistics from a rectangular, finite matrix.
    void fit(const Matrix& data);
    // Apply stored statistics; fit must have been called first.
    Matrix transform(const Matrix& data) const;
    // Fit on data and return its transformed values in one call.
    Matrix fit_transform(const Matrix& data);
    // Restore values to the original scale using the stored fit statistics.
    Matrix inverse_transform(const Matrix& data) const;
    // Report whether fit has successfully stored scaling statistics.
    bool is_fitted() const noexcept;

private:
    static void validate(const Matrix& data);
    Matrix apply(const Matrix& data, bool inverse) const;

    Method method_;
    std::vector<long double> offsets_;
    std::vector<long double> scales_;
    bool fitted_ = false;
};

#endif // FEATURE_SCALER_HPP
