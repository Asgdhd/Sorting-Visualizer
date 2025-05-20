#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "ArrayGenerator.hpp"
#include "ArrayVisualizer.hpp"
#include "Button.hpp"
#include "SortingAlgorithms.hpp"

namespace SortingVisualizer {
enum class Screen {
    MainScreen,
    BubbleSortScreen,
    SelectionSortScreen,
    InsertionSortScreen
};

struct AppState {
    std::vector<int> array;
    ArrayGenerator::ArrayType arrayType = ArrayGenerator::ArrayType::Random;
    size_t arraySize = 20;
    bool sortingActive = false;
    bool sortingCompleted = false;
    float visualizationHeight = 0.f;
    sf::Clock clock;
    Sorting::BubbleSort bubbleSorter;
    Sorting::SelectionSort selectionSorter;
    Sorting::InsertionSort insertionSorter;
    Sorting::SortingAlgorithm* currentSorter = nullptr;
};

void StartApp();
}  // namespace SortingVisualizer
