#include "Button.hpp"

namespace Button {
Button::Button() : isClicked(false), isEnabled(true) {
}

Button::Button(float x, float y, float width, float height, sf::Font& font, std::string text, sf::Color normalColor, sf::Color hoverColor,
               sf::Color pressedColor)
    : normalColor(normalColor), hoverColor(hoverColor), pressedColor(pressedColor), isClicked(false), isEnabled(true) {
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(normalColor);
    currentColor = normalColor;

    this->font = font;
    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(20);
    this->text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
                           shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);
}

void Button::update(const sf::Vector2i& mousePos) {
    // Hover
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        currentColor = hoverColor;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            currentColor = pressedColor;
            isClicked = true;
        } else {
            currentColor = hoverColor;
            isClicked = false;
        }
    } else {
        currentColor = normalColor;
        isClicked = false;
    }

    shape.setFillColor(currentColor);
}

void Button::render(sf::RenderTarget& target) {
    target.draw(shape);
    target.draw(text);
}
}  // namespace Button
