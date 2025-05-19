#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
#include "ArrayVisualizer.hpp"
#include "SortingAlgorithms.hpp"
#include "ArrayGenerator.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>

namespace SortingVisualizer {
    enum class Screen {
        MainScreen,
        BubbleSortScreen,
        SelectionSortScreen
    };

    struct AppState {
        std::vector<int> array;
        ArrayGenerator::ArrayType arrayType;
        size_t arraySize = 20;
        bool sortingActive = false;
        bool sortingCompleted = false;
        float visualizationHeight = 0.f;
        sf::Clock clock;
        Sorting::BubbleSort bubbleSorter;
        Sorting::SelectionSort selectionSorter;
        Sorting::SortingAlgorithm* currentSorter;
    };


    void StartApp();
}
