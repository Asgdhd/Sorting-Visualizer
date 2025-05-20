#pragma once
#include <vector>
#include <utility>

namespace Sorting {

    enum class ArrayType {
        Random, NearlySorted, Reversed, ManyDuplicates
    };

    class ArrayGenerator {
    public:
        static std::vector<int> generate(size_t size, ArrayType type);
    };

    class BubbleSort {
    private:
        size_t i = 0, j = 0;
        bool swapping = false;
        size_t idx1 = 0, idx2 = 0;
    public:
        void sort(std::vector<int>& arr, bool& done, float dt);
        void reset() { i = j = 0; swapping = false; }
        bool isSwappingState() const { return swapping; }
        std::pair<size_t, size_t> getSwapIndices() const { return {idx1, idx2}; }
        float getSwapProgress() const { return swapping ? 1.f : 0.f; }
    };
}
