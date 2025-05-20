#include "Button.hpp"

namespace Button {
template<typename T>
Button<T>::Button() : isClicked(false), isEnabled(true) {
}

template<typename T>
Button<T>::Button(float x, float y, float width, float height, sf::Font& font, std::string text, sf::Color normalColor, sf::Color hoverColor,
                  sf::Color pressedColor, sf::Color unabledColor, T message)
    : normalColor(normalColor),
      hoverColor(hoverColor),
      pressedColor(pressedColor),
      unabledColor(unabledColor),
      isClicked(false),
      isEnabled(true),
      message(message) {
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

template<typename T>
void Button<T>::update(const sf::Vector2i& mousePos) {
    if (!isEnabled) {
        currentColor = unabledColor;
        return;
    }

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

template<typename T>
void Button<T>::render(sf::RenderTarget& target) {
    target.draw(shape);
    target.draw(text);
}

template<typename T>
T Button<T>::getMessage() const {
    return message;
}
}  // namespace Button
