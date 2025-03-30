#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Button.hpp"

namespace SortingVisualizer {
enum class Screen {
    MainScreen,
    FirstScreen,
    SecondScreen,
    ThirdScreen
};

void StartApp();

void RenderMainWindow(sf::RenderWindow& window, Screen& currentScreen, std::vector<Button::Button<Screen>> mainScreenButtons,
                      Button::Button<Screen> backButton, std::vector<sf::Text> texts);
void RenderalgorithmWindow(sf::RenderWindow& window, sf::Vector2i& mousePos, Screen& currentScreen, Button::Button<Screen>& backButton,
                           sf::Text& text);

}  // namespace SortingVisualizer
