#include "ArrayModel.hpp"
#include <numeric>
#include <algorithm>
#include <random>

ArrayModel::ArrayModel(size_t size) {
    if (size == 0) size = 1;
    data_.resize(size);
    generateRandom();
}

void ArrayModel::generateRandom() {
    std::iota(data_.begin(), data_.end(), 1);
    std::shuffle(data_.begin(), data_.end(),
                 std::mt19937{ std::random_device{}() });
    sorter_.reset();
    done_ = false;
}

bool ArrayModel::step(float deltaTime) {
    if (done_) return true;
    sorter_.sort(data_, done_, deltaTime);
    return done_;
}

void ArrayModel::reset() {
    sorter_.reset();
    done_ = false;
}

const std::vector<int>& ArrayModel::getData() const {
    return data_;
}

bool ArrayModel::isSwapping() const {
    return sorter_.isSwappingState();
}

std::pair<size_t, size_t> ArrayModel::getSwapIndices() const {
    return sorter_.getSwapIndices();
}

float ArrayModel::getSwapProgress() const {
    return sorter_.getSwapProgress();
}
