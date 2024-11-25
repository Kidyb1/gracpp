#include <SFML/Graphics.hpp>
#include "EnemyWeak.h"
#include "EnemyFast.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Multiple Enemies Example");
    window.setFramerateLimit(60);

    // Gracz
    sf::CircleShape player(20.0f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.0f, 300.0f);

    // Przeciwnicy
    EnemyWeak weakEnemy(sf::Vector2f(200.0f, 300.0f));
    EnemyFast fastEnemy(sf::Vector2f(600.0f, 300.0f));

    float playerSpeed = 200.0f;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Ruch gracza
        sf::Vector2f movement(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += playerSpeed;

        sf::Time deltaTime = clock.restart();
        player.move(movement * deltaTime.asSeconds());

        // Aktualizacja przeciwników
        weakEnemy.update(player.getPosition(), deltaTime.asSeconds());
        fastEnemy.update(player.getPosition(), deltaTime.asSeconds());

        // Rysowanie
        window.clear();
        window.draw(player);
        weakEnemy.draw(window);
        fastEnemy.draw(window);
        window.display();
    }

    return 0;
}
