#ifndef ENEMY_WEAK_H
#define ENEMY_WEAK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class EnemyWeak {
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
    EnemyWeak(sf::Vector2f position);

    void update(const sf::Vector2f& playerPosition, float deltaTime);
    void draw(sf::RenderWindow& window);
};

#endif // ENEMY_WEAK_H
