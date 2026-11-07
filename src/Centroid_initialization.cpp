// Implements seeded or random selection of distinct data rows for initial centroids.
// Input validation ensures every selected point has the same finite feature vector shape.

// Copies in the header that declares the class CentroidInitializer.
// Without it, this file would not know the class exists.
// The quotes mean "look in my project"; k_means/ is a subfolder, so the
// compiler needs the option "-I include" to find it.
#include "k_means/Centroid_initialization.hpp"

// std::shuffle: mixes a list into a random order.
#include <algorithm>
// std::isfinite: checks that a number is not infinity or NaN (not a number).
#include <cmath>
// std::iota: fills a list with 0, 1, 2, 3, ...
#include <numeric>
// std::invalid_argument: the error type thrown when the input is not valid.
#include <stdexcept>


// ---------------------------------------------------------------------------
// Constructor 1: random seed.
// "CentroidInitializer::CentroidInitializer" = the class name, then the
// function name (a constructor has the same name as its class).
// After the ":" is the initializer list, which sets the members before the
// body runs:
//   k_(k)  -> store the given k.
//   gen_(std::random_device{}()) -> create a random device (real randomness
//            from the computer), call it once to get one random number, and
//            use that number as the seed of the generator gen_.
//            Result: a different random choice every time the program runs.
// ---------------------------------------------------------------------------
CentroidInitializer::CentroidInitializer(int k) : k_(k), gen_(std::random_device{}()) {
    // Safety check: k must be 1 or more. If not, stop with an error message,
    // so an object with a bad k can never be created.
    if (k < 1) throw std::invalid_argument("k must be at least 1.");
}

// ---------------------------------------------------------------------------
// Constructor 2: fixed seed.
// Same as constructor 1, but the seed is given by the caller.
// The same seed gives the same shuffle every time, so results can be
// repeated. This is useful for tests and examples.
// ---------------------------------------------------------------------------
CentroidInitializer::CentroidInitializer(int k, unsigned int seed) : k_(k), gen_(seed) {
    // Same safety check as in constructor 1.
    //A seed is a starting number that a random number generator uses to begin its sequence of “random” numbers.
    if (k < 1) throw std::invalid_argument("k must be at least 1.");
}

// ---------------------------------------------------------------------------
// getK: returns the stored value of k.
// The "const" at the end is a promise that this function does not change
// the object, so it can also be used on constant objects.
// ---------------------------------------------------------------------------
int CentroidInitializer::getK() const {
    return k_;
}

// ---------------------------------------------------------------------------
// setK: changes the stored value of k.
// ---------------------------------------------------------------------------
void CentroidInitializer::setK(int k) {
    // Check first. If k is bad, throw an error. Because the throw happens
    // before the next line, k_ keeps its old value.
    if (k < 1) throw std::invalid_argument("k must be at least 1.");
    // Only reached when k is valid.
    k_ = k;
}

// ---------------------------------------------------------------------------
// initialize: the main function.
// Returns k different points from the data, chosen at random, to be used
// as the starting centroids.
//   Return type: Dataset (a list of points). It is written as
//                CentroidInitializer::Dataset because Dataset is defined
//                inside the class.
//   Input:       "const Dataset& data" = a read-only reference. "const" means
//                the function cannot change your data, and "&" means the data
//                is not copied.
// ---------------------------------------------------------------------------
CentroidInitializer::Dataset CentroidInitializer::initialize(const Dataset& data) {
    // An empty list that will hold the chosen centroids.
    Dataset centroids;

    // ---- Step 1: Check the input ----

    // With no points there is nothing to choose from.
    if (data.empty()) throw std::invalid_argument("Data must not be empty.");

    // We cannot pick more different points than exist.
    // k_ is a signed int and data.size() is unsigned (size_t), so static_cast
    // converts k_ to size_t so the two can be compared safely. This is safe
    // because k_ is already known to be at least 1.
    if (static_cast<std::size_t>(k_) > data.size()) throw std::invalid_argument("k cannot exceed the number of data points.");

    // The number of features (numbers) in the first point, for example 2 for
    // {1, 1}. "auto" lets the compiler choose the type. This is the reference
    // size that all other points must match.
    const auto dimensions = data.front().size();

    // A point with no numbers, like {}, is useless, so it is rejected.
    if (dimensions == 0) throw std::invalid_argument("Points must contain at least one feature.");

    // Go through every point. "const auto&" = each point, read-only, no copy.
    for (const auto& point : data) {
        // Every point must have the same number of features as the first one.
        // A "ragged" dataset such as {{1, 2}, {3}} is rejected.
        if (point.size() != dimensions) throw std::invalid_argument("All data points must have the same dimension.");

        // Go through each number in the point. "!" means "not". If a number
        // is infinity or NaN, throw an error, because such values would
        // break the distance and mean calculations later.
        for (double value : point) if (!std::isfinite(value)) throw std::invalid_argument("Data values must be finite.");
    }

    // ---- Step 2: Choose k different random points ----

    // List every index 0..n-1, then shuffle them randomly
    // A list of integers with the same length as the data. The values are
    // not set yet.
    std::vector<int> indices(data.size());

    // Fill the list with 0, 1, 2, ... For 5 points it becomes {0, 1, 2, 3, 4}.
    // begin() and end() mark the start and the end of the list.
    std::iota(indices.begin(), indices.end(), 0);

    // Mix the list into a random order using the random generator gen_.
    // It might become {3, 0, 4, 1, 2}. Each number appears exactly once, so
    // none can repeat.
    std::shuffle(indices.begin(), indices.end(), gen_);

    // The first k shuffled indices are k unique random points
    // For each of the first k_ numbers in the shuffled list:
    //   data[indices[i]] = the point at that position in the data,
    //   push_back        = add it to the end of the centroids list.
    // Because the indices are unique, the chosen points are unique too.
    for (int i = 0; i < k_; i++) {
        centroids.push_back(data[indices[i]]);
    }

    // Give the chosen centroids back to the caller.
    return centroids;
}
