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

    explicit FeatureScaler(Method method = Method::MinMax);

    void fit(const Matrix& data);
    Matrix transform(const Matrix& data) const;
    Matrix fit_transform(const Matrix& data);
    Matrix inverse_transform(const Matrix& data) const;
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
