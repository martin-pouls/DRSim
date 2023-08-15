#include "HistogramData.h"
#include <algorithm>
#include <cmath>

namespace drsim {
HistogramData::HistogramData(const std::vector<int>& values, int min, int step)
    : min(min)
    , max(*std::max_element(values.begin(), values.end()))
    , step(step)
    , numBuckets(std::ceil(max / static_cast<double>(step)))
    , boundaries(initializeBoundaries())
    , counts(initializeCounts(values)) {
}

std::vector<int> HistogramData::initializeBoundaries() {
    std::vector<int> boundaries(numBuckets + 1, 0);
    for (int i = 0; i < numBuckets + 1; ++i) {
        boundaries[i] = min + step * i;
    }
    return boundaries;
}

std::vector<int> HistogramData::initializeCounts(const std::vector<int>& values) {
    std::vector<int> counts(numBuckets, 0);
    for (auto& value : values) {
        for (auto i = 0; i < counts.size(); ++i) {
            if (value >= boundaries[i] && value < boundaries[i + 1]) {
                ++counts[i];
                break;
            }
        }
    }
    return counts;
}

const std::vector<int>& HistogramData::getBoundaries() const {
    return boundaries;
}

const std::vector<int>& HistogramData::getCounts() const {
    return counts;
}

} // namespace drsim