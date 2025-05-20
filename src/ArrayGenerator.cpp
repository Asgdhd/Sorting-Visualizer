#include "ArrayGenerator.hpp"
#include <algorithm>

namespace ArrayGenerator {
std::vector<int> ArrayGenerator::generate(size_t size, ArrayType type) {
    std::vector<int> arr(size);
    std::iota(arr.begin(), arr.end(), 1);

    switch (type) {
        case ArrayType::Random: {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(arr.begin(), arr.end(), g);
            break;
        }
        case ArrayType::NearlySorted: {
            if (size >= 2)
                std::swap(arr[size / 3], arr[size / 2]);
            break;
        }
        case ArrayType::Reversed: {
            std::reverse(arr.begin(), arr.end());
            break;
        }
        case ArrayType::ManyDuplicates: {
            for (size_t i = 1; i < size; i += 2)
                arr[i] = arr[i - 1];
            std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});
            break;
        }
    }
    return arr;
}

}  // namespace ArrayGenerator
