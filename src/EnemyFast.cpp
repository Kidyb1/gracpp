#include "EnemyFast.h"

// Konstruktor przeciwnika
EnemyFast::EnemyFast(sf::Vector2f position)
    : speed(150.0f), visionRange(400.0f) {
    shape.setSize(sf::Vector2f(30.0f, 30.0f));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(position);
}

float EnemyFast::distance(const sf::Vector2f& a, const sf::Vector2f& b) const {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void EnemyFast::update(const sf::Vector2f& playerPosition, float deltaTime) {
    sf::Vector2f enemyCenter = shape.getPosition() + sf::Vector2f(shape.getSize().x / 2.0f, shape.getSize().y / 2.0f);

    // Sprawdzanie, czy gracz jest w zasięgu
    if (distance(enemyCenter, playerPosition) <= visionRange) {
        sf::Vector2f direction = playerPosition - enemyCenter;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalizacja kierunku i ruch przeciwnika
        if (length != 0) {
            direction /= length;
            shape.move(direction * speed * deltaTime);
        }
    }
}

void EnemyFast::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
