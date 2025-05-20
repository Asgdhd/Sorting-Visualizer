#pragma once
#include <SFML/Graphics.hpp>

namespace Button {
template<typename T>
class Button {
 private:
    sf::Text text;
    sf::Font font;
    sf::RectangleShape shape;

    sf::Color currentColor;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    sf::Color unabledColor;

    T message;

 public:
    bool isClicked;
    bool isEnabled;

    Button() : isClicked(false), isEnabled(true) {}

    Button(float x, float y, float width, float height, sf::Font& font, const std::string& text, sf::Color normalColor, sf::Color hoverColor,
           sf::Color pressedColor, sf::Color unabledColor, T message)
        : normalColor(normalColor),
          hoverColor(hoverColor),
          pressedColor(pressedColor),
          unabledColor(unabledColor),
          isClicked(false),
          isEnabled(true),
          message(message) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(normalColor);

        this->text.setFont(font);
        this->text.setString(text);
        this->text.setCharacterSize(20);
        this->text.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = this->text.getLocalBounds();
        this->text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        this->text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void setText(const std::string& newText) {
        text.setString(newText);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(shape.getPosition().x + shape.getSize().x / 2.0f, shape.getPosition().y + shape.getSize().y / 2.0f);
    }

    void update(const sf::Vector2i& mousePos) {
        if (!isEnabled) {
            currentColor = unabledColor;
            shape.setFillColor(currentColor);
            return;
        }

        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            currentColor = hoverColor;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                currentColor = pressedColor;
                isClicked = true;
            } else {
                isClicked = false;
            }
        } else {
            currentColor = normalColor;
            isClicked = false;
        }
        shape.setFillColor(currentColor);
    }

    void render(sf::RenderTarget& target) {
        target.draw(shape);
        target.draw(text);
    }

    T getMessage() const { return message; }
};
}  // namespace Button
