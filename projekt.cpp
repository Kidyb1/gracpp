#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "EnemyWeak.h"
#include "EnemyFast.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Walls Example");
    window.setFramerateLimit(60);

    sf::CircleShape player(20.0f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.0f, 300.0f);
    float playerSpeed = 200.0f;

    EnemyWeak weakEnemy(sf::Vector2f(200.0f, 300.0f));
    EnemyFast fastEnemy(sf::Vector2f(600.0f, 300.0f));

    std::vector<Wall> walls = {
        Wall(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(200.0f, 20.0f)),
        Wall(sf::Vector2f(400.0f, 150.0f), sf::Vector2f(20.0f, 300.0f)),
        Wall(sf::Vector2f(600.0f, 400.0f), sf::Vector2f(150.0f, 20.0f))
    };

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f movement(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += playerSpeed;

        sf::Time deltaTime = clock.restart();
        sf::Vector2f nextPosition = player.getPosition() + movement * deltaTime.asSeconds();

        bool collision = false;
        for (const auto& wall : walls) {
            if (wall.getShape().getGlobalBounds().intersects(
                    sf::FloatRect(nextPosition, sf::Vector2f(player.getRadius() * 2, player.getRadius() * 2)))) {
                collision = true;
                break;
            }
        }

        if (!collision) {
            player.move(movement * deltaTime.asSeconds());
        }

        weakEnemy.update(player.getPosition(), deltaTime.asSeconds());
        fastEnemy.update(player.getPosition(), deltaTime.asSeconds());

        window.clear();

        window.draw(player);

        for (auto& wall : walls) {
            wall.draw(window);
        }

        weakEnemy.draw(window);
        fastEnemy.draw(window);

        window.display();
    }

    return 0;
}
