#include <iostream>
#include <vector>

#include "SortingVisualizer.hpp"

namespace {
float kWindowSizeFactor = 0.8f;
float kFirstButtonWidthFactor = 0.1f;
float kFirstButtonHeightFactor = 0.2f;
float kButtonPositionStep = 3.f;

float kAlgorithmButtonWidth = 250.f;
float kAlgorithmButtonHeight = 70.f;

size_t kAlgorithmsNumber = 3;
unsigned int limit = 50;
}  // namespace

namespace SortingVisualizer {
void StartApp() {
    sf::Font font;

    if (!font.loadFromFile("../assets/font.ttf")) {
        exit(1);
    }

    unsigned int width = sf::VideoMode::getDesktopMode().width * kWindowSizeFactor;
    unsigned int height = sf::VideoMode::getDesktopMode().height * kWindowSizeFactor;

    sf::Vector2u screenSize = sf::Vector2u(width, height);

    sf::RenderWindow window(sf::VideoMode(width, height), "Sorting Visualizer", sf::Style::Close);

    window.setFramerateLimit(limit);

    Screen currentScreen = Screen::MainScreen;

    // main screen
    float step = 1.f;
    Button::Button button1(width * step * kFirstButtonWidthFactor, height * kFirstButtonHeightFactor, kAlgorithmButtonWidth, kAlgorithmButtonHeight,
                           font, "Go to Screen 1", sf::Color::Green, sf::Color::Cyan, sf::Color::Blue, sf::Color::White, Screen::FirstScreen);
    step += kButtonPositionStep;
    Button::Button button2(width * step * kFirstButtonWidthFactor, height * kFirstButtonHeightFactor, kAlgorithmButtonWidth, kAlgorithmButtonHeight,
                           font, "Go to Screen 2", sf::Color::Green, sf::Color::Cyan, sf::Color::Blue, sf::Color::White, Screen::SecondScreen);
    step += kButtonPositionStep;
    Button::Button button3(width * step * kFirstButtonWidthFactor, height * kFirstButtonHeightFactor, kAlgorithmButtonWidth, kAlgorithmButtonHeight,
                           font, "Go to Screen 3", sf::Color::Green, sf::Color::Cyan, sf::Color::Blue, sf::Color::White, Screen::ThirdScreen);

    std::vector<Button::Button<Screen>> mainScreenButtons{button1, button2, button3};
    // 1st screen

    Button::Button backButton(100, 400, 200, 50, font, "Back to Main Menu", sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta, sf::Color::White,
                               Screen::MainScreen);


    sf::Text Text1("This is Screen 1", font, 30);
    sf::Text Text2("This is Screen 2", font, 30);
    sf::Text Text3("This is Screen 3", font, 30);
    std::vector<sf::Text> texts{Text1, Text2, Text3};

    for (size_t i = 0; i < texts.size(); ++i) {
        texts[i].setPosition(100, 50);
        texts[i].setFillColor(sf::Color::White);
    }

    RenderMainWindow(window, currentScreen, mainScreenButtons, backButton, texts);
}

void RenderMainWindow(sf::RenderWindow& window, Screen& currentScreen, std::vector<Button::Button<Screen>> mainScreenButtons,
    Button::Button<Screen> BackButton, std::vector<sf::Text> texts) {
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
                for (size_t i = 0; i < mainScreenButtons.size(); ++i) {
                    mainScreenButtons[i].update(mousePos);
                    mainScreenButtons[i].render(window);

                    if (mainScreenButtons[i].isClicked) {
                        currentScreen = mainScreenButtons[i].getMessage();
                    }
                }

                break;

            case Screen::FirstScreen:
                RenderalgorithmWindow(window, mousePos, currentScreen, BackButton, texts[0]);
                break;

            case Screen::SecondScreen:
                RenderalgorithmWindow(window, mousePos, currentScreen, BackButton, texts[1]);
                break;
            case Screen::ThirdScreen:
                RenderalgorithmWindow(window, mousePos, currentScreen, BackButton, texts[2]);
                break;
            default:
                currentScreen = Screen::MainScreen;
        }

        window.display();
    }
}

void RenderalgorithmWindow(sf::RenderWindow& window, sf::Vector2i& mousePos, Screen& currentScreen, Button::Button<Screen>& backButton,
                           sf::Text& text) {
    backButton.update(mousePos);

    window.draw(text);
    backButton.render(window);

    if (backButton.isClicked) {
        currentScreen = Screen::MainScreen;
    }
}
}  // namespace SortingVisualizer
