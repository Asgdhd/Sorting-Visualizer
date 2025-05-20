#include "ArrayVisualizer.hpp"
#include <algorithm>

ArrayVisualizer::ArrayVisualizer(sf::RenderWindow& win, float vh)
: window(win), visHeight(vh)
{
    if (visHeight <= 0.f) visHeight = 1.f;
    updateWindowSize();
}

void ArrayVisualizer::setArray(const std::vector<int>& arr) {
    array = arr;
    updateWindowSize();
}

void ArrayVisualizer::updateWindowSize() {
    if (array.empty()) {
        columnWidth = 0.f;
        return;
    }
    float winWidth = static_cast<float>(window.getSize().x);
    if (winWidth <= 0.f) winWidth = 1.f;
    columnWidth = winWidth / static_cast<float>(array.size());
}

void ArrayVisualizer::draw(bool isSwapping,
                           std::pair<size_t, size_t> swapIdx,
                           float swapProgress)
{
    if (array.empty() || visHeight <= 0.f) return;

    const int N = array.size();
    float maxVal = static_cast<float>(*std::max_element(array.begin(), array.end()));
    if (maxVal <= 0.f) maxVal = 1.f;

    for (int i = 0; i < N; ++i) {
        float height = (static_cast<float>(array[i]) / maxVal) * visHeight;
        sf::RectangleShape rect;

        float gap = std::min(1.f, columnWidth * 0.1f);
        float barWidth = std::max(columnWidth - gap, 1.f);

        rect.setSize({barWidth, height});
        rect.setPosition(i * columnWidth + gap/2, visHeight - height);
        rect.setFillColor(sf::Color(200, 200, 200));

        if (isSwapping && (i == int(swapIdx.first) || i == int(swapIdx.second))) {
            rect.setFillColor(sf::Color::Red);
        }

        window.draw(rect);
    }
}
