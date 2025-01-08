#include "EnemyWeak.h"

// Konstruktor przeciwnika
EnemyWeak::EnemyWeak(sf::Vector2f position)
    : visionAngle(45.0f), visionRange(300.0f), currentAngle(0.0f),
      rotationDirection(1.0f), rotationSpeed(60.0f), bulletSpeed(400.0f),
      shootingCooldown(sf::seconds(1.0f)) {
    shape.setSize(sf::Vector2f(30.0f, 30.0f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

float EnemyWeak::distance(const sf::Vector2f& a, const sf::Vector2f& b) const {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void EnemyWeak::update(const sf::Vector2f& playerPosition, float deltaTime) {
    // Rozglądanie przeciwnika (obrót lewo-prawo)
    currentAngle += rotationDirection * rotationSpeed * deltaTime;
    if (currentAngle > visionAngle) rotationDirection = -1.0f;
    if (currentAngle < -visionAngle) rotationDirection = 1.0f;

    // Obliczenie kierunku patrzenia przeciwnika
    sf::Vector2f enemyCenter = shape.getPosition() + sf::Vector2f(shape.getSize().x / 2.0f, shape.getSize().y / 2.0f);
    sf::Vector2f visionDirection(cos(currentAngle * 3.14f / 180.0f), sin(currentAngle * 3.14f / 180.0f));

    // Sprawdzanie, czy gracz jest w polu widzenia przeciwnika
    bool playerInVision = false;
    sf::Vector2f toPlayer = playerPosition - enemyCenter;
    float angleToPlayer = atan2(toPlayer.y, toPlayer.x) * 180.0f / 3.14f;

    if (distance(enemyCenter, playerPosition) < visionRange &&
        std::abs(angleToPlayer - currentAngle) < visionAngle) {
        playerInVision = true;
    }

    // Strzelanie przeciwnika
    if (playerInVision && shootingClock.getElapsedTime() > shootingCooldown) {
        sf::CircleShape bullet(5.0f);
        bullet.setFillColor(sf::Color::Yellow);
        bullet.setPosition(enemyCenter);
        bullets.push_back(bullet);
        shootingClock.restart();
    }

    // Aktualizacja pocisków
    for (auto& bullet : bullets) {
        bullet.move(visionDirection * bulletSpeed * deltaTime);
    }
}

void EnemyWeak::draw(sf::RenderWindow& window) {
    // Rysowanie przeciwnika
    window.draw(shape);

    // Rysowanie pocisków
    for (const auto& bullet : bullets) {
        window.draw(bullet);
    }
}
