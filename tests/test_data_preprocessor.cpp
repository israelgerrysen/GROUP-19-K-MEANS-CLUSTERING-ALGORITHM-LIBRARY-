#include "k_means/DataPreprocessor.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {
template <typename Exception, typename Action>
bool throws(Action&& action) {
    try { action(); } catch (const Exception&) { return true; }
    return false;
}
}

int main() {
    using Dataset = std::vector<std::vector<double>>;

    Dataset dropped{{1, 2, 3}, {4, 5, 6}};
    DataPreprocessor::dropColumn(dropped, 1);
    assert(dropped == Dataset({{1, 3}, {4, 6}}));
    assert(throws<std::out_of_range>([&] { DataPreprocessor::dropColumn(dropped, -1); }));
    assert(throws<std::out_of_range>([&] { DataPreprocessor::dropColumn(dropped, 2); }));

    Dataset rows{{1, 2}, {3, std::numeric_limits<double>::quiet_NaN()}, {5, 6}};
    DataPreprocessor::dropRowsWithMissingData(rows);
    assert(rows == Dataset({{1, 2}, {5, 6}}));

    Dataset mean{{1, 10}, {3, std::numeric_limits<double>::quiet_NaN()}, {5, 30}};
    DataPreprocessor::fillMissingWithMean(mean);
    assert(mean[1][1] == 20);

    Dataset median{{1}, {std::numeric_limits<double>::quiet_NaN()}, {9}, {3}};
    DataPreprocessor::fillMissingWithMedian(median);
    assert(median[1][0] == 3);

    Dataset mode{{2}, {std::numeric_limits<double>::quiet_NaN()}, {2}, {3}};
    DataPreprocessor::fillMissingWithMode(mode);
    assert(mode[1][0] == 2);

    Dataset encoded{{10}, {20}, {30}};
    DataPreprocessor::oneHotEncode(encoded, {"B", "A", "B"});
    assert(encoded == Dataset({{10, 0, 1}, {20, 1, 0}, {30, 0, 1}}));
    assert(throws<std::invalid_argument>([&] { DataPreprocessor::oneHotEncode(encoded, {"only one"}); }));

    assert(throws<std::invalid_argument>([] {
        Dataset allMissing{{std::numeric_limits<double>::quiet_NaN()},
                           {std::numeric_limits<double>::quiet_NaN()}};
        DataPreprocessor::fillMissingWithMean(allMissing);
    }));
    assert(throws<std::invalid_argument>([] {
        Dataset ragged{{1, 2}, {3}};
        DataPreprocessor::dropRowsWithMissingData(ragged);
    }));
    assert(throws<std::invalid_argument>([] {
        Dataset infinite{{1, std::numeric_limits<double>::infinity()}};
        DataPreprocessor::fillMissingWithMedian(infinite);
    }));
}
