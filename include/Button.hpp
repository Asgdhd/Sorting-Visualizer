#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Button {

template<typename T>
class Button {
private:
    sf::Text text;
    sf::RectangleShape shape;
    sf::Color normal, hover, pressed, disabled;
    T message;

public:
    bool isClicked = false;
    bool isEnabled = true;

    Button() = default;

    Button(float x, float y, float w, float h,
           sf::Font& font, const std::string& str,
           sf::Color normalColor, sf::Color hoverColor,
           sf::Color pressedColor, sf::Color disabledColor,
           T msg)
        : normal(normalColor)
        , hover(hoverColor)
        , pressed(pressedColor)
        , disabled(disabledColor)
        , message(msg)
    {
        shape.setPosition(x, y);
        shape.setSize({ w, h });
        shape.setFillColor(normal);

        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(static_cast<unsigned>(h * 0.5f));
        text.setFillColor(sf::Color::Black);

        auto tb = text.getLocalBounds();
        text.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
        text.setPosition(x + w / 2.0f, y + h / 2.0f);
    }

    void update(const sf::Vector2i& mousePos) {
        isClicked = false;

        if (!isEnabled) {
            shape.setFillColor(disabled);
            return;
        }

        bool inside = shape.getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y)
        );

        if (inside && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shape.setFillColor(pressed);
        }
        else if (inside) {
            shape.setFillColor(hover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                isClicked = true;
            }
        }
        else {
            shape.setFillColor(normal);
        }
    }

    void render(sf::RenderTarget& target) {
        target.draw(shape);
        target.draw(text);
    }

    T getMessage() const {
        return message;
    }
};

}
