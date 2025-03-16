#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Button.hpp"


namespace SortingVisualizer{
    enum class Screen {
        MainScreen,
        FirstScreen,
        SecondScreen
    };

    void StartApp();
    void RenderWindow(sf::RenderWindow& window, Screen& currentScreen, Button::Button& mainMenuButton1,
        Button::Button& mainMenuButton2, Button::Button& screenOneBackButton, Button::Button& screenTwoBackButton, sf::Text& screenOneText,
        sf::Text& screenTwoText);
    }
