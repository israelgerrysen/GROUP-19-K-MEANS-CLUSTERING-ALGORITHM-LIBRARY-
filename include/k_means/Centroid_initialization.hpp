// API for choosing k distinct input rows as the initial K-Means centroids.
// The optional seed constructor makes initialization repeatable for tests and examples.
#ifndef INITIALIZE_CENTROID
#define INITIALIZE_CENTROID
#include <vector>
#include <random>
#include <stdexcept>


//initializeCentroids function declaration: initializes k centroids by randomly selecting existing data points)
class CentroidInitializer {
public:
    using Point   = std::vector<double>;
    using Dataset = std::vector<Point>;

    explicit CentroidInitializer(int k);
    CentroidInitializer(int k, unsigned int seed);

    int  getK() const;
    void setK(int k);

    // Select k distinct rows. Throws invalid_argument for invalid k, empty,
    // ragged, or non-finite data.
    Dataset initialize(const Dataset& data);

private:
    int          k_;
    std::mt19937 gen_;
};

#endif // CENTROID_INITIALIZATION_HPP
