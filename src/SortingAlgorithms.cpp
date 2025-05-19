#include "SortingAlgorithms.hpp"


namespace Sorting {
    void BubbleSort::sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) {
        sortingCompleted = false;

        if (isSwapping) {
            const float swapDuration = 0.2f;
            swapProgress += deltaTime / swapDuration;
            if (swapProgress >= 1.0f) {
                std::swap(array[swapIndex1], array[swapIndex2]);
                swapCount++;
                isSwapping = false;
                swapProgress = 0.0f;
                j++;
                swapped = true;
            }
        } else {
            if (i < array.size() - 1) {
                if (j < array.size() - i - 1) {
                    comparisonCount++;
                    if (array[j] > array[j + 1]) {
                        isSwapping = true;
                        swapIndex1 = j;
                        swapIndex2 = j + 1;
                        swapProgress = 0.0f;
                    } else {
                        j++;
                    }
                } else {
                    if (!swapped) {
                        sortingCompleted = true;
                        i = array.size();
                    } else {
                        swapped = false;
                        i++;
                        j = 0;
                    }
                }
            } else {
                sortingCompleted = true;
                i = 0;
                j = 0;
            }
        }
    }

    void BubbleSort::reset() {
        i = 0;
        j = 0;
        isSwapping = false;
        swapIndex1 = 0;
        swapIndex2 = 0;
        swapProgress = 0.0f;
        resetCounters();
    }

    void BubbleSort::resetCounters() {
        swapCount = 0;
        comparisonCount = 0;
    }

    size_t BubbleSort::getSwapCount() const { return swapCount; }
    size_t BubbleSort::getComparisonCount() const { return comparisonCount; }
    bool BubbleSort::isSwappingState() const { return isSwapping; }
    std::pair<size_t, size_t> BubbleSort::getSwapIndices() const { return {swapIndex1, swapIndex2}; }
    float BubbleSort::getSwapProgress() const { return swapProgress; }

    void SelectionSort::sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) {
        sortingCompleted = false;

        if (isSwapping) {
            const float swapDuration = 0.2f;
            swapProgress += deltaTime / swapDuration;
            if (swapProgress >= 1.0f) {
                std::swap(array[swapIndex1], array[swapIndex2]);
                swapCount++;
                isSwapping = false;
                swapProgress = 0.0f;
                i++;
                j = i + 1;
                minIndex = i;
            }
        } else if (i < array.size() - 1) {
            if (j < array.size()) {
                comparisonCount++;
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
                j++;
            } else {
                if (minIndex != i) {
                    swapIndex1 = i;
                    swapIndex2 = minIndex;
                    isSwapping = true;
                } else {
                    i++;
                    j = i + 1;
                    minIndex = i;
                }
            }
        } else {
            sortingCompleted = true;
            i = 0;
            j = 0;
        }
    }

    void SelectionSort::reset() {
        i = 0;
        j = 0;
        minIndex = 0;
        isSwapping = false;
        swapIndex1 = 0;
        swapIndex2 = 0;
        swapProgress = 0.0f;
        resetCounters();
    }

    void SelectionSort::resetCounters() {
        swapCount = 0;
        comparisonCount = 0;
    }

    size_t SelectionSort::getSwapCount() const { return swapCount; }
    size_t SelectionSort::getComparisonCount() const { return comparisonCount; }
    bool SelectionSort::isSwappingState() const { return isSwapping; }
    std::pair<size_t, size_t> SelectionSort::getSwapIndices() const { return {swapIndex1, swapIndex2}; }
    float SelectionSort::getSwapProgress() const { return swapProgress; }
}
