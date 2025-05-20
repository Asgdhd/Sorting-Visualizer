#include <SFML/System.hpp>
#include <algorithm>
#include <stack>
#include <vector>

namespace Sorting {
class SortingAlgorithm {
 public:
    virtual ~SortingAlgorithm() = default;
    virtual void sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) = 0;
    virtual void reset() = 0;
    virtual void resetCounters() = 0;
    virtual size_t getSwapCount() const = 0;
    virtual size_t getComparisonCount() const = 0;
    virtual bool isSwappingState() const = 0;
    virtual std::pair<size_t, size_t> getSwapIndices() const = 0;
    virtual float getSwapProgress() const = 0;
};

class BubbleSort : public SortingAlgorithm {
 private:
    size_t i = 0;
    size_t j = 0;
    bool isSwapping = false;
    size_t swapIndex1 = 0;
    size_t swapIndex2 = 0;
    float swapProgress = 0.f;
    size_t swapCount = 0;
    size_t comparisonCount = 0;
    bool swapped = false;

 public:
    BubbleSort() = default;
    void sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) override;
    void reset() override;
    void resetCounters() override;
    size_t getSwapCount() const override;
    size_t getComparisonCount() const override;
    bool isSwappingState() const override;
    std::pair<size_t, size_t> getSwapIndices() const override;
    float getSwapProgress() const override;
};

class SelectionSort : public SortingAlgorithm {
 private:
    size_t i = 0;
    size_t minIndex = 0;
    size_t j = 0;
    bool isSwapping = false;
    size_t swapIndex1 = 0;
    size_t swapIndex2 = 0;
    float swapProgress = 0.f;
    size_t swapCount = 0;
    size_t comparisonCount = 0;

 public:
    SelectionSort() = default;
    void sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) override;
    void reset() override;
    void resetCounters() override;
    size_t getSwapCount() const override;
    size_t getComparisonCount() const override;
    bool isSwappingState() const override;
    std::pair<size_t, size_t> getSwapIndices() const override;
    float getSwapProgress() const override;
};
class InsertionSort : public SortingAlgorithm {
 private:
    size_t i = 1;
    size_t j = 1;
    bool isSwapping = false;
    size_t swapIndex1 = 0;
    size_t swapIndex2 = 0;
    float swapProgress = 0.f;
    size_t swapCount = 0;
    size_t comparisonCount = 0;
    int currentValue = 0;
    bool initialized = false;

 public:
    InsertionSort() = default;
    void sort(std::vector<int>& array, bool& sortingCompleted, float deltaTime) override;
    void reset() override;
    void resetCounters() override;
    size_t getSwapCount() const override;
    size_t getComparisonCount() const override;
    bool isSwappingState() const override;
    std::pair<size_t, size_t> getSwapIndices() const override;
    float getSwapProgress() const override;
};
}  // namespace Sorting
