#include "SortingVisualizer.hpp"

namespace {
constexpr float kWindowSizeFactor = 0.8f;
const sf::Color kMainColor(40, 40, 55);
const sf::Color kButtonColor(80, 120, 200);
const sf::Color kHoverColor(100, 150, 250);
const sf::Color kDisabledColor(100, 100, 100);
}  // namespace

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

    SortingVisualizer::AppState state;
    state.visualizationHeight = height * 0.8f;
    state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, ArrayGenerator::ArrayType::Random);

    ArrayVisualizer visualizer(window, state.visualizationHeight);

    std::vector<Button::Button<SortingVisualizer::Screen>> mainButtons;
    mainButtons.emplace_back(width * 0.5f - width * 0.1f, height * 0.25f, width * 0.2f, height * 0.05f, font, "Bubble Sort", kButtonColor,
                             kHoverColor, sf::Color::White, kDisabledColor, SortingVisualizer::Screen::BubbleSortScreen);
    mainButtons.emplace_back(width * 0.5f - width * 0.1f, height * 0.35f, width * 0.2f, height * 0.05f, font, "Selection Sort", kButtonColor,
                             kHoverColor, sf::Color::White, kDisabledColor, SortingVisualizer::Screen::SelectionSortScreen);
    mainButtons.emplace_back(width * 0.5f - width * 0.1f, height * 0.45f, width * 0.2f, height * 0.05f, font, "Insertion Sort", kButtonColor,
                             kHoverColor, sf::Color::White, kDisabledColor, SortingVisualizer::Screen::InsertionSortScreen);

    Button::Button<SortingVisualizer::Screen> backButton(width * 0.02f, height * 0.02f, width * 0.1f, height * 0.04f, font, "Back",
                                                         sf::Color(200, 80, 80), sf::Color(220, 100, 100), sf::Color::White, sf::Color::White,
                                                         SortingVisualizer::Screen::MainScreen);

    std::vector<Button::Button<ArrayGenerator::ArrayType>> arrayTypeButtons = {
        {width * 0.77f, height * 0.1f,  width * 0.15f, height * 0.03f, font, "Random",        kButtonColor, kHoverColor, sf::Color::White, kDisabledColor,
         ArrayGenerator::ArrayType::Random                                                                                                                                                          },
        {width * 0.77f, height * 0.15f, width * 0.15f, height * 0.03f, font, "Nearly Sorted", kButtonColor, kHoverColor, sf::Color::White,
         kDisabledColor,                                                                                                                                   ArrayGenerator::ArrayType::NearlySorted  },
        {width * 0.77f, height * 0.2f,  width * 0.15f, height * 0.03f, font, "Reversed",      kButtonColor, kHoverColor, sf::Color::White, kDisabledColor,
         ArrayGenerator::ArrayType::Reversed                                                                                                                                                        },
        {width * 0.77f, height * 0.25f, width * 0.15f, height * 0.03f, font, "Duplicates",    kButtonColor, kHoverColor, sf::Color::White,
         kDisabledColor,                                                                                                                                   ArrayGenerator::ArrayType::ManyDuplicates}
    };

    std::vector<Button::Button<size_t>> sizeButtons = {
        {width * 0.77f,                 height * 0.3f, width * 0.045f, height * 0.03f, font, "20", kButtonColor, kHoverColor, sf::Color::White, kDisabledColor, 20},
        {width * 0.77f + width * 0.05f, height * 0.3f, width * 0.045f, height * 0.03f, font, "30", kButtonColor, kHoverColor, sf::Color::White,
         kDisabledColor,                                                                                                                                        30},
        {width * 0.77f + width * 0.1f,  height * 0.3f, width * 0.045f, height * 0.03f, font, "40", kButtonColor, kHoverColor, sf::Color::White,
         kDisabledColor,                                                                                                                                        40}
    };

    Button::Button<bool> startButton(width * 0.77f, height * 0.35f, width * 0.07f, height * 0.04f, font, "Start", sf::Color(80, 200, 120),
                                     sf::Color(100, 220, 140), sf::Color::White, kDisabledColor, true);

    Button::Button<bool> resetButton(width * 0.77f + width * 0.08f, height * 0.35f, width * 0.07f, height * 0.04f, font, "Reset",
                                     sf::Color(200, 80, 80), sf::Color(220, 100, 100), sf::Color::White, sf::Color::White, true);

    sf::Text metricsText;
    metricsText.setFont(font);
    metricsText.setCharacterSize(static_cast<unsigned>(height * 0.025f));
    metricsText.setFillColor(sf::Color::White);
    metricsText.setPosition(width * 0.77f, height * 0.4f);

    SortingVisualizer::Screen currentScreen = SortingVisualizer::Screen::MainScreen;

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
            case SortingVisualizer::Screen::MainScreen: {
                for (auto& btn : mainButtons) {
                    btn.update(mousePos);
                    btn.render(window);
                    if (btn.isClicked) {
                        currentScreen = btn.getMessage();
                        state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                        if (currentScreen == SortingVisualizer::Screen::BubbleSortScreen) {
                            state.currentSorter = &state.bubbleSorter;
                        } else if (currentScreen == SortingVisualizer::Screen::SelectionSortScreen) {
                            state.currentSorter = &state.selectionSorter;
                        } else if (currentScreen == SortingVisualizer::Screen::InsertionSortScreen) {
                            state.currentSorter = &state.insertionSorter;
                        }
                        state.currentSorter->resetCounters();
                    }
                }
                break;
            }

            case SortingVisualizer::Screen::BubbleSortScreen:
            case SortingVisualizer::Screen::SelectionSortScreen: {
                if (currentScreen == SortingVisualizer::Screen::BubbleSortScreen) {
                    state.currentSorter = &state.bubbleSorter;
                } else {
                    state.currentSorter = &state.selectionSorter;
                }

                visualizer.setArray(state.array);
                visualizer.draw(state.currentSorter->isSwappingState(), state.currentSorter->getSwapIndices(),
                                state.currentSorter->getSwapProgress());

                for (auto& btn : arrayTypeButtons)
                    btn.isEnabled = !state.sortingActive;
                for (auto& btn : sizeButtons)
                    btn.isEnabled = !state.sortingActive;
                startButton.isEnabled = !state.sortingActive;

                backButton.update(mousePos);
                backButton.render(window);
                if (backButton.isClicked) {
                    currentScreen = SortingVisualizer::Screen::MainScreen;
                    state.sortingActive = false;
                    state.sortingCompleted = false;
                    state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                    state.currentSorter->reset();
                }

                for (auto& btn : arrayTypeButtons) {
                    btn.update(mousePos);
                    btn.render(window);
                    if (btn.isClicked && btn.isEnabled) {
                        state.arrayType = btn.getMessage();
                        state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                        state.currentSorter->resetCounters();
                    }
                }

                for (auto& btn : sizeButtons) {
                    btn.update(mousePos);
                    btn.render(window);
                    if (btn.isClicked && btn.isEnabled) {
                        state.arraySize = btn.getMessage();
                        state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                        state.currentSorter->resetCounters();
                    }
                }

                startButton.update(mousePos);
                startButton.render(window);
                if (startButton.isClicked && startButton.isEnabled) {
                    state.sortingActive = true;
                    state.sortingCompleted = false;
                    state.currentSorter->resetCounters();
                }

                resetButton.update(mousePos);
                resetButton.render(window);
                if (resetButton.isClicked) {
                    state.sortingActive = false;
                    state.sortingCompleted = false;
                    state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                    state.currentSorter->reset();
                }

                if (state.sortingActive && !state.sortingCompleted) {
                    state.currentSorter->sort(state.array, state.sortingCompleted, deltaTime);
                }

                std::stringstream ss;
                ss << "Swaps: " << state.currentSorter->getSwapCount() << "\n"
                   << "Comparisons: " << state.currentSorter->getComparisonCount();
                metricsText.setString(ss.str());
                window.draw(metricsText);

                break;
            }

            case SortingVisualizer::Screen::InsertionSortScreen: {
                state.currentSorter = &state.insertionSorter;
                visualizer.setArray(state.array);
                visualizer.draw(state.currentSorter->isSwappingState(), state.currentSorter->getSwapIndices(),
                                state.currentSorter->getSwapProgress());

                for (auto& btn : arrayTypeButtons)
                    btn.isEnabled = !state.sortingActive;
                for (auto& btn : sizeButtons)
                    btn.isEnabled = !state.sortingActive;
                startButton.isEnabled = !state.sortingActive;

                backButton.update(mousePos);
                backButton.render(window);
                if (backButton.isClicked) {
                    currentScreen = SortingVisualizer::Screen::MainScreen;
                    state.sortingActive = false;
                    state.sortingCompleted = false;
                    state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                    state.currentSorter->reset();
                }

                for (auto& btn : arrayTypeButtons) {
                    btn.update(mousePos);
                    btn.render(window);
                    if (btn.isClicked && btn.isEnabled) {
                        state.arrayType = btn.getMessage();
                        state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                        state.currentSorter->resetCounters();
                    }
                }

                for (auto& btn : sizeButtons) {
                    btn.update(mousePos);
                    btn.render(window);
                    if (btn.isClicked && btn.isEnabled) {
                        state.arraySize = btn.getMessage();
                        state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                        state.currentSorter->resetCounters();
                    }
                }

                startButton.update(mousePos);
                startButton.render(window);
                if (startButton.isClicked && startButton.isEnabled) {
                    state.sortingActive = true;
                    state.sortingCompleted = false;
                    state.currentSorter->resetCounters();
                }

                resetButton.update(mousePos);
                resetButton.render(window);
                if (resetButton.isClicked) {
                    state.sortingActive = false;
                    state.sortingCompleted = false;
                    state.array = ArrayGenerator::ArrayGenerator::generate(state.arraySize, state.arrayType);
                    state.currentSorter->reset();
                }

                if (state.sortingActive && !state.sortingCompleted) {
                    state.currentSorter->sort(state.array, state.sortingCompleted, deltaTime);
                }

                std::stringstream ss;
                ss << "Swaps: " << state.currentSorter->getSwapCount() << "\n"
                   << "Comparisons: " << state.currentSorter->getComparisonCount();
                metricsText.setString(ss.str());
                window.draw(metricsText);

                break;
            }
        }

        window.display();
    }
}
}  // namespace SortingVisualizer
