#ifndef INITIALIZE_CENTROID
#define INITIALIZE_CENTROID
#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <numeric>
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

    Dataset initialize(const Dataset& data);

private:
    int          k_;
    std::mt19937 gen_;
};

#endif // CENTROID_INITIALIZATION_HPP