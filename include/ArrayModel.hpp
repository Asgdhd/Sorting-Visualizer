#pragma once
#include <vector>
#include "SortingAlgorithms.hpp"

class ArrayModel {
public:
    ArrayModel(size_t size = 50);

    void generateRandom();
    bool step(float deltaTime);
    void reset();

    const std::vector<int>& getData() const;
    bool isSwapping() const;
    std::pair<size_t, size_t> getSwapIndices() const;
    float getSwapProgress() const;

private:
    std::vector<int> data_;
    Sorting::BubbleSort sorter_;
    bool done_ = false;
};
