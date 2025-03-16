#pragma once

#include <SFML/Graphics.hpp>

namespace Button {
class Button {
 private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    sf::Color currentColor;
    bool isEnabled;

 public:
    bool isClicked;
    Button();
    Button(float x, float y, float width, float height, sf::Font& font, std::string text, sf::Color normalColor, sf::Color hoverColor,
           sf::Color pressedColor);
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderTarget& target);
};

}  // namespace Button
