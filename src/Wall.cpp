#include "Wall.h"

// Konstruktor ściany
Wall::Wall(sf::Vector2f position, sf::Vector2f size) {
    shape.setSize(size);
    shape.setFillColor(sf::Color::Blue); // Kolor ściany
    shape.setPosition(position);
}

// Rysowanie ściany
void Wall::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Getter dla kształtu
const sf::RectangleShape& Wall::getShape() const {
    return shape;
}
