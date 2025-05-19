#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class ArrayVisualizer {
private:
    sf::RenderWindow& window;
    std::vector<int> array;
    float columnWidth;
    float visualizationHeight;

public:
    ArrayVisualizer(sf::RenderWindow& win, float visHeight);
    void setArray(const std::vector<int>& arr);
    void draw(bool isSwapping, std::pair<size_t, size_t> swapIndices, float swapProgress);
};
