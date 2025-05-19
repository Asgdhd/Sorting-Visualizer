#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
#include "ArrayVisualizer.hpp"
#include "SortingAlgorithms.hpp"

namespace SortingVisualizer {
    enum class Screen {
        MainScreen,
        BubbleSortScreen
    };

    struct AppState {
        std::vector<int> array;
        Sorting::ArrayType arrayType = Sorting::ArrayType::Random;
        size_t arraySize = 20;
        bool sortingActive = false;
        bool sortingCompleted = false;
        float visualizationHeight = 0.f;
        Sorting::BubbleSort sorter;
        sf::Clock clock;
    };

    void StartApp();
}
