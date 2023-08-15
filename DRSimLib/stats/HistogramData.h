#pragma once
#include <vector>

namespace drsim {
    class HistogramData {
    public:
        HistogramData(const std::vector<int>& values, int min, int step);
        const std::vector<int>& getBoundaries() const;
        const std::vector<int>& getCounts() const;

    private:
        int min;
        int max;
        int step;
        unsigned numBuckets;
        
        std::vector<int> boundaries;
        std::vector<int> counts;

        std::vector<int> initializeBoundaries();
        std::vector<int> initializeCounts(const std::vector<int>& values);
    };
}