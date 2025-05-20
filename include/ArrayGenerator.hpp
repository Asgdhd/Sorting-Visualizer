#pragma once
#include <numeric>
#include <random>
#include <vector>

namespace ArrayGenerator {
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
}  // namespace ArrayGenerator
