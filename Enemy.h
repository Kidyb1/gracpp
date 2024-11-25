#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Enemy {
private:
    sf::RectangleShape shape;
    float visionAngle; // Kąt widzenia
    float visionRange; // Zasięg widzenia
    float currentAngle; // Aktualny kąt patrzenia przeciwnika
    float rotationDirection; // Kierunek obracania (1 = prawo, -1 = lewo)
    float rotationSpeed; // Szybkość obracania
    sf::Clock shootingClock; // Do kontrolowania strzałów
    sf::Time shootingCooldown; // Czas między strzałami
    std::vector<sf::CircleShape> bullets; // Pociski przeciwnika
    float bulletSpeed; // Szybkość pocisków

    // Funkcja pomocnicza do obliczania odległości
    float distance(const sf::Vector2f& a, const sf::Vector2f& b) const;

public:
    Enemy(sf::Vector2f position);

    void update(const sf::Vector2f& playerPosition, float deltaTime);
    void draw(sf::RenderWindow& window);
};

#endif // ENEMY_H
