#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "ArrayVisualizer.hpp"
#include "ArrayModel.hpp"
#include "SortingAlgorithms.hpp"

namespace SortingVisualizer {
    enum class Screen { Main, Bubble };
    struct AppState {
        std::vector<int> array;
        ArrayModel model;
        bool active = false, done = false;
        float visH = 0.f;
        sf::Clock clock;
    };
    void StartApp();
}
