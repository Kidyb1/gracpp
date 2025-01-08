#ifndef ENEMY_FAST_H
#define ENEMY_FAST_H

#include <SFML/Graphics.hpp>
#include <cmath>

class EnemyFast {
private:
    sf::RectangleShape shape;
    float speed; // Szybkość przeciwnika
    float visionRange; // Zasięg widzenia

    // Funkcja pomocnicza do obliczania odległości
    float distance(const sf::Vector2f& a, const sf::Vector2f& b) const;

public:
    EnemyFast(sf::Vector2f position);

    void update(const sf::Vector2f& playerPosition, float deltaTime);
    void draw(sf::RenderWindow& window);
};

#endif // ENEMY_FAST_H
