#include "SortingAlgorithms.hpp"
#include <algorithm>
#include <random>

namespace Sorting {
    std::vector<int> ArrayGenerator::generate(size_t size, ArrayType type) {
        std::vector<int> arr(size);
        std::iota(arr.begin(), arr.end(), 1);

        switch(type) {
            case ArrayType::Random: {
                std::random_device rd;
                std::shuffle(arr.begin(), arr.end(), rd);
                break;
            }
            case ArrayType::NearlySorted:
                if (size >= 2) std::swap(arr[size/3], arr[size/2]);
                break;
            case ArrayType::Reversed:
                std::reverse(arr.begin(), arr.end());
                break;
            case ArrayType::ManyDuplicates:
                for (size_t i = 1; i < size; i += 2) arr[i] = arr[i-1];
                std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});
                break;
        }
        return arr;
    }

    BubbleSort::BubbleSort() : i(0), j(0), isSwapping(false), swapIndex1(0), swapIndex2(0), swapProgress(0.f), swapCount(0), comparisonCount(0) {}

    void BubbleSort::sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) {
        sortingCompleted = false;

        if (isSwapping) {
            const float swapDuration = 0.2f;
            swapProgress += deltaTime / swapDuration;
            if (swapProgress >= 1.f) {
                std::swap(array[swapIndex1], array[swapIndex2]);
                swapCount++;
                isSwapping = false;
                swapProgress = 0.f;
                j++;
            }
        } else if (i < array.size() - 1) {
            if (j < array.size() - i - 1) {
                comparisonCount++;
                if (array[j] > array[j + 1]) {
                    isSwapping = true;
                    swapIndex1 = j;
                    swapIndex2 = j + 1;
                    swapProgress = 0.f;
                } else {
                    j++;
                }
            } else {
                j = 0;
                i++;
            }
        } else {
            sortingCompleted = true;
            isSwapping = false;
            swapProgress = 0.f;
            i = 0;
            j = 0;
        }
    }

    void BubbleSort::reset() {
        i = 0;
        j = 0;
        isSwapping = false;
        swapIndex1 = 0;
        swapIndex2 = 0;
        swapProgress = 0.f;
        resetCounters();
    }

    void BubbleSort::resetCounters() {
        swapCount = 0;
        comparisonCount = 0;
    }

    size_t BubbleSort::getSwapCount() const {
        return swapCount;
    }

    size_t BubbleSort::getComparisonCount() const {
        return comparisonCount;
    }

    bool BubbleSort::isSwappingState() const {
        return isSwapping;
    }

    std::pair<size_t, size_t> BubbleSort::getSwapIndices() const {
        return {swapIndex1, swapIndex2};
    }

    float BubbleSort::getSwapProgress() const {
        return swapProgress;
    }
}
