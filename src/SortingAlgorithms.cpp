#include "SortingAlgorithms.hpp"
#include <numeric>
#include <algorithm>
#include <random>

namespace Sorting {

std::vector<int> ArrayGenerator::generate(size_t size, ArrayType type) {
    std::vector<int> a(size);
    std::iota(a.begin(), a.end(), 1);
    std::mt19937 rng{std::random_device{}()};
    switch(type){
    case ArrayType::Random:
        std::shuffle(a.begin(), a.end(), rng);
        break;
    case ArrayType::Reversed:
        std::reverse(a.begin(), a.end());
        break;
    case ArrayType::NearlySorted:
        std::shuffle(a.begin(), a.begin() + size/5, rng);
        break;
    case ArrayType::ManyDuplicates:
        for(auto& v: a) v = rng()% (size/5 +1);
        break;
    }
    return a;
}

void BubbleSort::sort(std::vector<int>& arr, bool& done, float) {
    size_t n = arr.size();
    if (n == 0) {
        done = true;
        return;
    }
    if (i >= n-1) {
        done = true;
        return;
    }
    if (!swapping) {
        if (j < n - i - 1) {
            if (arr[j] > arr[j+1]) {
                swapping = true;
                idx1 = j; idx2 = j+1;
                std::swap(arr[j], arr[j+1]);
            }
            ++j;
        } else {
            j = 0;
            ++i;
        }
    } else {
        swapping = false;
    }
}
}
