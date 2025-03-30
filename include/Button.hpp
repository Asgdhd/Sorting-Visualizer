#pragma once

#include <SFML/Graphics.hpp>

namespace Button {
template<typename T>
class Button {
 private:
    sf::Text text;
    sf::Font font;

    sf::Color currentColor;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    sf::Color unabledColor;
    T message;

 public:
    sf::RectangleShape shape;
    bool isClicked;
    bool isEnabled;

    Button();
    Button(float x, float y, float width, float height, sf::Font& font, std::string text, sf::Color normalColor, sf::Color hoverColor,
           sf::Color pressedColor, sf::Color unabledColor, T message);
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderTarget& target);

    T getMessage();
};

}  // namespace Button

#include "../src/Button.tpp"
