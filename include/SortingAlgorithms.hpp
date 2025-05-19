#pragma once
#include <vector>

namespace Sorting {
    enum class ArrayType {
        Random,
        NearlySorted,
        Reversed,
        ManyDuplicates
    };

    class ArrayGenerator {
    public:
        static std::vector<int> generate(size_t size, ArrayType type);
    };

    class BubbleSort {
    private:
        size_t i;
        size_t j;
        bool isSwapping;
        size_t swapIndex1;
        size_t swapIndex2;
        float swapProgress;
        size_t swapCount;
        size_t comparisonCount;

    public:
        BubbleSort();
        void sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime);
        void reset();
        void resetCounters();
        size_t getSwapCount() const;
        size_t getComparisonCount() const;
        bool isSwappingState() const;
        std::pair<size_t, size_t> getSwapIndices() const;
        float getSwapProgress() const;
    };
}
