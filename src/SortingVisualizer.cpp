#include <iostream>

#include "SortingVisualizer.hpp"

namespace SortingVisualizer {
void StartApp() {
    sf::Font font;

    if (!font.loadFromFile("../assets/font.ttf")){
        exit(1);
    }

    unsigned int width = sf::VideoMode::getDesktopMode().width * 0.8f;
    unsigned int height = sf::VideoMode::getDesktopMode().height * 0.8f;

    sf::Vector2u screenSize = sf::Vector2u(width, height);

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML Navigation", sf::Style::Close);

    window.setFramerateLimit(10);

    Screen currentScreen = Screen::MainScreen;

    // main screen
    Button::Button mainMenuButton1(100, 100, 200, 50, font, "Go to Screen 1", sf::Color::Green, sf::Color::Cyan, sf::Color::Blue);
    Button::Button mainMenuButton2(100, 200, 200, 50, font, "Go to Screen 2", sf::Color::Green, sf::Color::Cyan, sf::Color::Blue);

    // 1st screen
    Button::Button screenOneBackButton(100, 400, 200, 50, font, "Back to Main Menu", sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta);
    sf::Text screenOneText("This is Screen 1", font, 30);
    screenOneText.setPosition(100, 50);
    screenOneText.setFillColor(sf::Color::White);

    // 2nd screen
    Button::Button screenTwoBackButton(100, 400, 200, 50, font, "Back to Main Menu", sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta);
    sf::Text screenTwoText("This is Screen 2", font, 30);
    screenTwoText.setPosition(100, 50);
    screenTwoText.setFillColor(sf::Color::White);

    RenderWindow(window, currentScreen, mainMenuButton1, mainMenuButton2, screenOneBackButton, screenTwoBackButton, screenOneText, screenTwoText);
}

void RenderWindow(sf::RenderWindow& window, Screen& currentScreen, Button::Button& mainMenuButton1, Button::Button& mainMenuButton2,
                  Button::Button& screenOneBackButton, Button::Button& screenTwoBackButton, sf::Text& screenOneText, sf::Text& screenTwoText) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        switch (currentScreen) {
            case Screen::MainScreen:
                mainMenuButton1.update(mousePos);
                mainMenuButton2.update(mousePos);

                mainMenuButton1.render(window);
                mainMenuButton2.render(window);

                if (mainMenuButton1.isClicked) {
                    currentScreen = Screen::FirstScreen;
                }
                if (mainMenuButton2.isClicked) {
                    currentScreen = Screen::SecondScreen;
                }
                break;

            case Screen::FirstScreen:
                screenOneBackButton.update(mousePos);

                window.draw(screenOneText);
                screenOneBackButton.render(window);

                if (screenOneBackButton.isClicked) {
                    currentScreen = Screen::MainScreen;
                }
                break;

            case Screen::SecondScreen:
                screenTwoBackButton.update(mousePos);

                window.draw(screenTwoText);
                screenTwoBackButton.render(window);

                if (screenTwoBackButton.isClicked) {
                    currentScreen = Screen::MainScreen;
                }
                break;
        }

        window.display();
    }
}
}  // namespace SortVisualizer
