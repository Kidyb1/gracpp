#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game with flashlight vision");
    window.setFramerateLimit(60);

    // Postać gracza - okrąg
    sf::CircleShape player(20.0f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.0f, 300.0f);

    // Przeszkody - ściany
    sf::RectangleShape wall1(sf::Vector2f(200.0f, 30.0f));
    wall1.setFillColor(sf::Color::Red);
    wall1.setPosition(150.0f, 200.0f);

    sf::RectangleShape wall2(sf::Vector2f(200.0f, 30.0f));
    wall2.setFillColor(sf::Color::Red);
    wall2.setPosition(450.0f, 400.0f);

    float playerSpeed = 150.0f; // Piksele na sekundę
    sf::Clock clock; // Do mierzenia czasu

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Ruch postaci z ograniczeniem kolizji
        sf::Vector2f movement(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += playerSpeed;

        sf::Time deltaTime = clock.restart();
        sf::Vector2f newPosition = player.getPosition() + movement * deltaTime.asSeconds();

        // Kolizje ze ścianami
        player.setPosition(newPosition);
        if (player.getGlobalBounds().intersects(wall1.getGlobalBounds()) ||
            player.getGlobalBounds().intersects(wall2.getGlobalBounds())) {
            player.setPosition(player.getPosition() - movement * deltaTime.asSeconds()); // Cofanie ruchu przy kolizji
        }

        // Obliczanie kierunku latarki
        sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getRadius(), player.getRadius());
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f direction = mousePosition - playerCenter;
        float angle = atan2(direction.y, direction.x);

        // Kształt latarki (stożek)
        sf::ConvexShape flashlight;
        flashlight.setPointCount(3);
        flashlight.setPoint(0, playerCenter);
        flashlight.setPoint(1, playerCenter + sf::Vector2f(300.0f * cos(angle - 0.3f), 300.0f * sin(angle - 0.3f)));
        flashlight.setPoint(2, playerCenter + sf::Vector2f(300.0f * cos(angle + 0.3f), 300.0f * sin(angle + 0.3f)));
        flashlight.setFillColor(sf::Color(255, 255, 255, 150)); // Białe, półprzezroczyste światło

        // Rysowanie
        window.clear();
        window.draw(wall1);
        window.draw(wall2);
        window.draw(player);

        // Rysowanie latarki
        window.draw(flashlight);

        window.display();
    }

    return 0;
}
