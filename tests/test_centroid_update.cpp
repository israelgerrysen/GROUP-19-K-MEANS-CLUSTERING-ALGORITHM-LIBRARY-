#include "k_means/Centroid_Update.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
int checks = 0;
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) { std::cerr << "FAIL: " << message << "\n"; std::exit(1); }
}
bool near(double a, double b) { return std::abs(a - b) <= 1e-9 * (1.0 + std::abs(b)); }
template <typename Exception, typename Function>
void throws(Function action, const char* message) {
    bool caught = false;
    try { action(); } catch (const Exception&) { caught = true; }
    require(caught, message);
}
}

int main() {
    using Dataset = CentroidUpdater::Dataset;

    const Dataset data{{0, 0}, {2, 2}, {10, 10}, {12, 14}};
    const Dataset old{{0, 0}, {10, 10}};

    // mean of each cluster
    auto updated = CentroidUpdater::update(data, {0, 0, 1, 1}, old);
    require(updated.size() == 2, "one centroid per cluster");
    require(near(updated[0][0], 1) && near(updated[0][1], 1), "mean of cluster 0");
    require(near(updated[1][0], 11) && near(updated[1][1], 12), "mean of cluster 1");

    // all points in one cluster
    updated = CentroidUpdater::update(data, {0, 0, 0, 0}, Dataset{{9, 9}});
    require(near(updated[0][0], 6) && near(updated[0][1], 6.5), "single cluster mean");

    // a cluster with one point: centroid moves onto that point
    updated = CentroidUpdater::update(Dataset{{3, 4}}, {0}, Dataset{{0, 0}});
    require(updated[0] == CentroidUpdater::Point({3, 4}), "one point -> centroid is that point");

    // empty cluster keeps its old centroid
    updated = CentroidUpdater::update(data, {0, 0, 1, 1}, Dataset{{0, 0}, {10, 10}, {50, 50}});
    require(updated.size() == 3, "still three centroids");
    require(updated[2] == CentroidUpdater::Point({50, 50}), "empty cluster keeps old centroid");

    // 1-D data and negative values
    updated = CentroidUpdater::update(Dataset{{-4}, {-2}, {6}}, {0, 0, 1}, Dataset{{0}, {0}});
    require(near(updated[0][0], -3) && near(updated[1][0], 6), "1-D and negative values");

    // labels do not need to be in order
    updated = CentroidUpdater::update(data, {1, 1, 0, 0}, old);
    require(near(updated[0][0], 11) && near(updated[1][0], 1), "labels follow centroid index");

    // inputs are not changed
    const Dataset dataCopy = data;
    const Dataset oldCopy = old;
    CentroidUpdater::update(data, {0, 0, 1, 1}, old);
    require(data == dataCopy && old == oldCopy, "inputs unchanged");

    // invalid input
    throws<std::invalid_argument>([&] { CentroidUpdater::update(Dataset{}, {}, old); }, "empty data");
    throws<std::invalid_argument>([&] { CentroidUpdater::update(data, {0, 0, 1, 1}, Dataset{}); }, "no centroids");
    throws<std::invalid_argument>([&] { CentroidUpdater::update(data, {0, 1}, old); }, "wrong number of labels");
    throws<std::invalid_argument>([&] { CentroidUpdater::update(data, {0, 0, 1, 2}, old); }, "label too large");
    throws<std::invalid_argument>([&] { CentroidUpdater::update(data, {0, 0, -1, 1}, old); }, "negative label");
    throws<std::invalid_argument>([&] { CentroidUpdater::update(data, {0, 0, 1, 1}, Dataset{{0}, {1}}); }, "dimension mismatch");
    throws<std::invalid_argument>([&] { CentroidUpdater::update(data, {0, 0, 1, 1}, Dataset{{0, 0}, {1}}); }, "centroids differ in size");
    throws<std::invalid_argument>([] { CentroidUpdater::update({{1, 2}}, {0}, {{}}); }, "zero-dimensional centroid");
    throws<std::invalid_argument>([] { CentroidUpdater::update({{std::numeric_limits<double>::infinity()}}, {0}, {{0}}); }, "non-finite data");
    throws<std::invalid_argument>([] { CentroidUpdater::update({{1}}, {0}, {{std::numeric_limits<double>::quiet_NaN()}}); }, "non-finite centroid");

    std::cout << "All " << checks << " checks passed.\n";
    return 0;
}
