#include "ArrayVisualizer.hpp"
#include <algorithm>

ArrayVisualizer::ArrayVisualizer(sf::RenderWindow& win, float visHeight)
    : window(win), visualizationHeight(visHeight) {}

void ArrayVisualizer::setArray(const std::vector<int>& arr) {
    array = arr;
    if (!array.empty()) {
        columnWidth = (window.getSize().x * 0.75f) / static_cast<float>(array.size());
    }
}

void ArrayVisualizer::draw(bool isSwapping, std::pair<size_t, size_t> swapIndices, float swapProgress) {
    if (array.empty()) return;

    float maxValue = *std::max_element(array.begin(), array.end());
    if (maxValue == 0) return;

    const float verticalPadding = visualizationHeight * 0.2f;
    const float verticalOffset = visualizationHeight * 0.3f;
    const float baseY = visualizationHeight - verticalPadding + verticalOffset;

    for (size_t i = 0; i < array.size(); ++i) {
        float height = (array[i] / maxValue) * (visualizationHeight - verticalPadding);
        sf::RectangleShape column(sf::Vector2f(columnWidth * 0.95f, height));


        float xPos = i * columnWidth + window.getSize().x * 0.01f;


        if (isSwapping && (i == swapIndices.first || i == swapIndices.second)) {
            size_t targetIndex = (i == swapIndices.first) ? swapIndices.second : swapIndices.first;
            float targetX = targetIndex * columnWidth + window.getSize().x * 0.01f;
            xPos = xPos + (targetX - xPos) * swapProgress;
            column.setFillColor(sf::Color(250, 100, 100));
        } else {
            column.setFillColor(sf::Color(100, 250, 150));
        }

        column.setPosition(xPos, baseY - height);
        window.draw(column);
    }
}
