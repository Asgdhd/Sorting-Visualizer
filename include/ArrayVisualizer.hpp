#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ArrayVisualizer {
private:
    sf::RenderWindow& window;
    std::vector<int> array;
    float columnWidth = 0.f;
    float visHeight;

public:
    ArrayVisualizer(sf::RenderWindow& win, float visHeight);
    void setArray(const std::vector<int>& arr);
    void draw(bool isSwapping,
              std::pair<size_t, size_t> swapIdx,
              float swapProgress);
    void updateWindowSize();
};
