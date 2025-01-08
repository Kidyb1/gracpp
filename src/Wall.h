#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall {
private:
    sf::RectangleShape shape; // Kształt ściany

public:
    Wall(sf::Vector2f position, sf::Vector2f size);

    void draw(sf::RenderWindow& window);
    const sf::RectangleShape& getShape() const; // Getter dla kształtu ściany
};

#endif // WALL_H
