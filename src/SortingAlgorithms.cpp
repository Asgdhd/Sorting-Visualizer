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

size_t SelectionSort::getSwapCount() const {
    return swapCount;
}
size_t SelectionSort::getComparisonCount() const {
    return comparisonCount;
}
bool SelectionSort::isSwappingState() const {
    return isSwapping;
}
std::pair<size_t, size_t> SelectionSort::getSwapIndices() const {
    return {swapIndex1, swapIndex2};
}
float SelectionSort::getSwapProgress() const {
    return swapProgress;
}

void InsertionSort::sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) {
    sortingCompleted = false;

    if (array.size() <= 1) {
        sortingCompleted = true;
        return;
    }

    if (!initialized) {
        i = 1;
        j = i;
        currentValue = array[i];
        initialized = true;
    }

    if (isSwapping) {
        const float swapDuration = 0.2f;
        swapProgress += deltaTime / swapDuration;
        if (swapProgress >= 1.0f) {
            array[j] = array[j - 1];
            swapCount++;
            j--;
            swapProgress = 0.0f;
            isSwapping = false;
        }
    } else {
        if (i < array.size()) {
            if (j > 0) {
                comparisonCount++;
                if (array[j - 1] > currentValue) {
                    isSwapping = true;
                    swapIndex1 = j;
                    swapIndex2 = j - 1;
                } else {
                    array[j] = currentValue;
                    i++;
                    if (i < array.size()) {
                        currentValue = array[i];
                        j = i;
                    }
                }
            } else {
                array[j] = currentValue;
                i++;
                if (i < array.size()) {
                    currentValue = array[i];
                    j = i;
                }
            }
        } else {
            sortingCompleted = true;
            initialized = false;
        }
    }
}

void InsertionSort::reset() {
    i = 1;
    j = 1;
    isSwapping = false;
    swapIndex1 = 0;
    swapIndex2 = 0;
    swapProgress = 0.0f;
    currentValue = 0;
    initialized = false;
    resetCounters();
}

void InsertionSort::resetCounters() {
    swapCount = 0;
    comparisonCount = 0;
}

size_t InsertionSort::getSwapCount() const {
    return swapCount;
}
size_t InsertionSort::getComparisonCount() const {
    return comparisonCount;
}
bool InsertionSort::isSwappingState() const {
    return isSwapping;
}
std::pair<size_t, size_t> InsertionSort::getSwapIndices() const {
    return {swapIndex1, swapIndex2};
}
float InsertionSort::getSwapProgress() const {
    return swapProgress;
}
}  // namespace Sorting
