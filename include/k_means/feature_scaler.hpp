#ifndef FEATURE_SCALER_HPP
#define FEATURE_SCALER_HPP

#include <vector>

class FeatureScaler {
public:
    using Matrix = std::vector<std::vector<double>>;
    enum class Method { MinMax, Standard };

    explicit FeatureScaler(Method method = Method::MinMax);
    void fit(const Matrix& data);
    [[nodiscard]] Matrix transform(const Matrix& data) const;
    [[nodiscard]] Matrix fit_transform(const Matrix& data);
    [[nodiscard]] Matrix inverse_transform(const Matrix& data) const;
    [[nodiscard]] bool is_fitted() const noexcept;

private:
    Method method_;
    bool fitted_ = false;
    std::vector<long double> offsets_;
    std::vector<long double> scales_;
    static void validate(const Matrix& data);
    [[nodiscard]] Matrix apply(const Matrix& data, bool inverse) const;
};

#endif
