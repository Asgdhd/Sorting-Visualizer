#include "SortingVisualizer.hpp"
#include <iostream>
#include <sstream>

namespace {
    constexpr float kWindowSizeFactor = 0.8f;
    const sf::Color kMainColor(40, 40, 55);
    const sf::Color kButtonColor(80, 120, 200);
    const sf::Color kHoverColor(100, 150, 250);
    const sf::Color kDisabledColor(100, 100, 100);
}

namespace SortingVisualizer {
    void StartApp() {
        sf::Font font;
        if (!font.loadFromFile("../assets/font.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            exit(1);
        }

        unsigned width = sf::VideoMode::getDesktopMode().width * kWindowSizeFactor;
        unsigned height = sf::VideoMode::getDesktopMode().height * kWindowSizeFactor;

        sf::RenderWindow window(sf::VideoMode(width, height), "Sorting Visualizer", sf::Style::Close);
        window.setFramerateLimit(60);

        AppState state;
        state.visualizationHeight = height * 0.8f;
        state.array = Sorting::ArrayGenerator::generate(state.arraySize, state.arrayType);

        ArrayVisualizer visualizer(window, state.visualizationHeight);

        std::vector<Button::Button<Screen>> mainButtons;
        mainButtons.emplace_back(
            width * 0.5f - width * 0.1f, height * 0.25f, width * 0.2f, height * 0.05f,
            font, "Bubble Sort",
            kButtonColor, kHoverColor, sf::Color::White, kDisabledColor,
            Screen::BubbleSortScreen
        );

        Button::Button<Screen> backButton(
            width * 0.02f, height * 0.02f, width * 0.1f, height * 0.04f,
            font, "Back",
            sf::Color(200, 80, 80), sf::Color(220, 100, 100),
            sf::Color::White, sf::Color::White,
            Screen::MainScreen
        );

        std::vector<Button::Button<Sorting::ArrayType>> arrayTypeButtons = {
            {width * 0.77f, height * 0.1f, width * 0.15f, height * 0.03f, font, "Random",
             kButtonColor, kHoverColor, sf::Color::White, kDisabledColor,
             Sorting::ArrayType::Random},
            {width * 0.77f, height * 0.15f, width * 0.15f, height * 0.03f, font, "Nearly Sorted",
             kButtonColor, kHoverColor, sf::Color::White, kDisabledColor,
             Sorting::ArrayType::NearlySorted},
            {width * 0.77f, height * 0.2f, width * 0.15f, height * 0.03f, font, "Reversed",
             kButtonColor, kHoverColor, sf::Color::White, kDisabledColor,
             Sorting::ArrayType::Reversed},
            {width * 0.77f, height * 0.25f, width * 0.15f, height * 0.03f, font, "Duplicates",
             kButtonColor, kHoverColor, sf::Color::White, kDisabledColor,
             Sorting::ArrayType::ManyDuplicates}
        };

        std::vector<Button::Button<size_t>> sizeButtons = {
            {width * 0.77f, height * 0.3f, width * 0.045f, height * 0.03f, font, "20",
             kButtonColor, kHoverColor, sf::Color::White, kDisabledColor, 20},
            {width * 0.77f + width * 0.05f, height * 0.3f, width * 0.045f, height * 0.03f, font, "30",
             kButtonColor, kHoverColor, sf::Color::White, kDisabledColor, 30},
            {width * 0.77f + width * 0.1f, height * 0.3f, width * 0.045f, height * 0.03f, font, "40",
             kButtonColor, kHoverColor, sf::Color::White, kDisabledColor, 40}
        };

        Button::Button<bool> startButton(
            width * 0.77f, height * 0.35f, width * 0.07f, height * 0.04f,
            font, "Start",
            sf::Color(80, 200, 120), sf::Color(100, 220, 140),
            sf::Color::White, kDisabledColor,
            true
        );

        Button::Button<bool> resetButton(
            width * 0.77f + width * 0.08f, height * 0.35f, width * 0.07f, height * 0.04f,
            font, "Reset",
            sf::Color(200, 80, 80), sf::Color(220, 100, 100),
            sf::Color::White, sf::Color::White,
            true
        );

        sf::Text metricsText;
        metricsText.setFont(font);
        metricsText.setCharacterSize(static_cast<unsigned>(height * 0.025f));
        metricsText.setFillColor(sf::Color::White);
        metricsText.setPosition(width * 0.77f, height * 0.4f);

        Screen currentScreen = Screen::MainScreen;
        while (window.isOpen()) {
            float deltaTime = state.clock.restart().asSeconds();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            window.clear(kMainColor);

            switch (currentScreen) {
                case Screen::MainScreen: {
                    for (auto& btn : mainButtons) {
                        btn.update(mousePos);
                        btn.render(window);
                        if (btn.isClicked) {
                            currentScreen = btn.getMessage();
                            state.array = Sorting::ArrayGenerator::generate(state.arraySize, state.arrayType);
                            state.sorter.resetCounters();
                        }
                    }
                    break;
                }

                case Screen::BubbleSortScreen: {
                    visualizer.setArray(state.array);
                    visualizer.draw(state.sorter.isSwappingState(), state.sorter.getSwapIndices(), state.sorter.getSwapProgress());

                    for (auto& btn : arrayTypeButtons) btn.isEnabled = !state.sortingActive;
                    for (auto& btn : sizeButtons) btn.isEnabled = !state.sortingActive;
                    startButton.isEnabled = !state.sortingActive;

                    backButton.update(mousePos);
                    backButton.render(window);
                    if (backButton.isClicked) {
                        currentScreen = Screen::MainScreen;
                        state.sortingActive = false;
                        state.sortingCompleted = false;
                        state.array = Sorting::ArrayGenerator::generate(state.arraySize, state.arrayType);
                        state.sorter.reset();
                    }

                    for (auto& btn : arrayTypeButtons) {
                        btn.update(mousePos);
                        btn.render(window);
                        if (btn.isClicked && btn.isEnabled) {
                            state.arrayType = btn.getMessage();
                            state.array = Sorting::ArrayGenerator::generate(state.arraySize, state.arrayType);
                            state.sorter.resetCounters();
                        }
                    }

                    for (auto& btn : sizeButtons) {
                        btn.update(mousePos);
                        btn.render(window);
                        if (btn.isClicked && btn.isEnabled) {
                            state.arraySize = btn.getMessage();
                            state.array = Sorting::ArrayGenerator::generate(state.arraySize, state.arrayType);
                            state.sorter.resetCounters();
                        }
                    }

                    startButton.update(mousePos);
                    startButton.render(window);
                    if (startButton.isClicked && startButton.isEnabled) {
                        state.sortingActive = true;
                        state.sortingCompleted = false;
                        state.sorter.resetCounters();
                    }

                    resetButton.update(mousePos);
                    resetButton.render(window);
                    if (resetButton.isClicked) {
                        state.sortingActive = false;
                        state.sortingCompleted = false;
                        state.array = Sorting::ArrayGenerator::generate(state.arraySize, state.arrayType);
                        state.sorter.reset();
                    }

                    if (state.sortingActive && !state.sortingCompleted) {
                        state.sorter.sort(state.array, state.sortingCompleted, deltaTime);
                    }

                    std::stringstream ss;
                    ss << "Swaps: " << state.sorter.getSwapCount() << "\n"
                       << "Comparisons: " << state.sorter.getComparisonCount();
                    metricsText.setString(ss.str());
                    window.draw(metricsText);

                    break;
                }
            }

            window.display();
        }
    }
}
