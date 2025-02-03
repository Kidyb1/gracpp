#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class StartMenu {
public:
    sf::Font font;
    sf::Text title, startButton, exitButton;

    StartMenu() {
        if (!font.loadFromFile("assets/fonts/Sansation1.ttf")) {
            std::cerr << "Nie można załadować czcionki!" << std::endl;
        }

        title.setFont(font);
        title.setString("Vlvl");
        title.setCharacterSize(50);
        title.setPosition(WINDOW_WIDTH / 2 - 50, 50);
        title.setFillColor(sf::Color::White);

        startButton.setFont(font);
        startButton.setString("Start");
        startButton.setCharacterSize(30);
        startButton.setPosition(WINDOW_WIDTH / 2 - 30, 200);
        startButton.setFillColor(sf::Color::Green);

        exitButton.setFont(font);
        exitButton.setString("Exit");
        exitButton.setCharacterSize(30);
        exitButton.setPosition(WINDOW_WIDTH / 2 - 30, 300);
        exitButton.setFillColor(sf::Color::Red);
    }
};

class Player {
public:
    sf::RectangleShape shape;
    float speed = 5.0f;

    Player() {
        shape.setSize(sf::Vector2f(40, 40));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(50, WINDOW_HEIGHT / 2);
    }

    void move(sf::Keyboard::Key key, const std::vector<sf::RectangleShape>& obstacles) {
        sf::Vector2f oldPos = shape.getPosition();
        if (key == sf::Keyboard::W) shape.move(0, -speed);
        if (key == sf::Keyboard::S) shape.move(0, speed);
        if (key == sf::Keyboard::A) shape.move(-speed, 0);
        if (key == sf::Keyboard::D) shape.move(speed, 0);

        for (const auto& obstacle : obstacles) {
            if (shape.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
                shape.setPosition(oldPos);
                break;
            }
        }
    }
};

class Enemy {
public:
    sf::RectangleShape shape;
    float speed = 0.04f;
    sf::Vector2f direction;
    bool avoidingObstacle = false;
    bool movingRightAfterAvoidance = false;
    float moveRightDistance = 50.0f;

    Enemy(float x, float y) {
        shape.setSize(sf::Vector2f(40, 40));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
        direction = sf::Vector2f(1.0f, 0.0f);
    }

    void chase(const sf::Vector2f& playerPos, std::vector<sf::RectangleShape>& obstacles) {
        sf::Vector2f oldPos = shape.getPosition();

        if (movingRightAfterAvoidance) {
            shape.move(speed * 10.0f, 0.0f);
            moveRightDistance -= speed * 10.0f;

            if (moveRightDistance <= 0) {
                movingRightAfterAvoidance = false;
                avoidingObstacle = false;
                moveRightDistance = 50.0f; // Reset dystansu do przesunięcia w prawo
            }
            return;
        }

        sf::Vector2f toPlayer = playerPos - shape.getPosition();
        float length = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

        if (length != 0 && !avoidingObstacle) {
            toPlayer /= length;
            shape.move(toPlayer * speed);
        }

        for (size_t i = 0; i < obstacles.size(); ++i) {
            if (shape.getGlobalBounds().intersects(obstacles[i].getGlobalBounds())) {
                shape.setPosition(oldPos);

                if (!avoidingObstacle) {
                    avoidingObstacle = true;

                    if (i == 0 || i == 2) {
                        direction = sf::Vector2f(0.0f, -1.0f); // Omijanie w górę
                    }
                    else if (i == 1) {
                        direction = sf::Vector2f(0.0f, 1.0f); // Omijanie w dół
                    }
                }

                shape.move(direction * speed * 10.0f);

                if (!obstacleInWay(obstacles)) {
                    movingRightAfterAvoidance = true;
                }
                return;
            }
        }
        avoidingObstacle = false;
    }

    bool obstacleInWay(const std::vector<sf::RectangleShape>& obstacles) {
        for (const auto& obstacle : obstacles) {
            if (shape.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
                return true;
            }
        }
        return false;
    }
};

class VerticalEnemy {
public:
    sf::RectangleShape shape;
    float speed;

    VerticalEnemy(float x, float y, float speed) : speed(speed) {
        shape.setSize(sf::Vector2f(150, 50));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);
    }

    void move() {
        shape.move(0, speed);
        if (shape.getPosition().y >= WINDOW_HEIGHT) {
            shape.setPosition(shape.getPosition().x, -shape.getSize().y); // Powrót do góry ekranu
        }
        if (shape.getPosition().y < -shape.getSize().y) {
            shape.setPosition(shape.getPosition().x, WINDOW_HEIGHT); // Powrót na dół ekranu
        }
    }
};

void resetPositions(Player& player, std::vector<Enemy>& enemies, std::vector<VerticalEnemy>& verticalEnemies) {
    player.shape.setPosition(50, WINDOW_HEIGHT / 2);

    for (auto& enemy : enemies) {
        enemy.shape.setPosition(0, 600);
    }

    for (auto& verticalEnemy : verticalEnemies) {
        verticalEnemy.shape.setPosition(verticalEnemy.shape.getPosition().x, 100); // Reset przykładowej pozycji pionowego przeciwnika
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Vlvl");
    StartMenu menu;
    Player player;
    sf::Clock gameClock; // Miernik czasu gry
    sf::Text congratulationsText, timeText;


    // Tekst gratulacyjny
    congratulationsText.setFont(menu.font);
    congratulationsText.setString("Gratulacje! Ukończyłeś grę!");
    congratulationsText.setCharacterSize(40);
    congratulationsText.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 100);
    congratulationsText.setFillColor(sf::Color::White);

    // Tekst z czasem gry
    timeText.setFont(menu.font);
    timeText.setCharacterSize(30);
    timeText.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2);
    timeText.setFillColor(sf::Color::Yellow);

    bool gameRunning = false;
    int currentLevel = 0;

    // Tworzenie poziomu 0
    std::vector<sf::RectangleShape> obstacles0 = {

    };
    sf::RectangleShape endPoint0(sf::Vector2f(50, 50));
    endPoint0.setFillColor(sf::Color::Yellow);
    endPoint0.setPosition(WINDOW_WIDTH - 70, WINDOW_HEIGHT / 2);

    // Tworzenie poziomu 1
    std::vector<sf::RectangleShape> obstacles1 = {
        sf::RectangleShape(sf::Vector2f(50, 500)),
        sf::RectangleShape(sf::Vector2f(50, -500)),
        sf::RectangleShape(sf::Vector2f(50, 500))
    };
    obstacles1[0].setFillColor(sf::Color::Red);
    obstacles1[0].setPosition(200, 100);
    obstacles1[1].setFillColor(sf::Color::Red);
    obstacles1[1].setPosition(400, 500);
    obstacles1[2].setFillColor(sf::Color::Red);
    obstacles1[2].setPosition(600, 100);

    sf::RectangleShape endPoint1(sf::Vector2f(50, 50));
    endPoint1.setFillColor(sf::Color::Yellow);
    endPoint1.setPosition(WINDOW_WIDTH - 70, WINDOW_HEIGHT / 2);

    // Tworzenie poziomu 2
    std::vector<sf::RectangleShape> obstacles2 = {
        sf::RectangleShape(sf::Vector2f(50, 500)),
        sf::RectangleShape(sf::Vector2f(50, -500)),
        sf::RectangleShape(sf::Vector2f(50, 500))
    };
    obstacles2[0].setFillColor(sf::Color::Red);
    obstacles2[0].setPosition(200, 100);
    obstacles2[1].setFillColor(sf::Color::Red);
    obstacles2[1].setPosition(400, 500);
    obstacles2[2].setFillColor(sf::Color::Red);
    obstacles2[2].setPosition(600, 100);

    sf::RectangleShape endPoint2(sf::Vector2f(50, 50));
    endPoint2.setFillColor(sf::Color::Yellow);
    endPoint2.setPosition(WINDOW_WIDTH - 70, WINDOW_HEIGHT / 2);

    std::vector<Enemy> enemies2 = {
        Enemy(0, 600),

    };

    // Tworzenie poziomu 3
    std::vector<sf::RectangleShape> obstacles3 = {
        sf::RectangleShape(sf::Vector2f(50, 500)),
        sf::RectangleShape(sf::Vector2f(50, -500)),
        sf::RectangleShape(sf::Vector2f(50, 500))
    };
    obstacles3[0].setFillColor(sf::Color::Red);
    obstacles3[0].setPosition(200, 100);
    obstacles3[1].setFillColor(sf::Color::Red);
    obstacles3[1].setPosition(400, 500);
    obstacles3[2].setFillColor(sf::Color::Red);
    obstacles3[2].setPosition(600, 100);

    sf::RectangleShape endPoint3(sf::Vector2f(50, 50));
    endPoint3.setFillColor(sf::Color::Yellow);
    endPoint3.setPosition(WINDOW_WIDTH - 70, WINDOW_HEIGHT / 2);

    std::vector<Enemy> enemies3 = {
        Enemy(0, 600),

    };

    std::vector<VerticalEnemy> verticalEnemies3 = {
        VerticalEnemy(250, 100, 0.08f),
        VerticalEnemy(450, 400, -0.08f)
    };
    // Tworzenie poziomu 4
    std::vector<sf::RectangleShape> obstacles4 = {
        sf::RectangleShape(sf::Vector2f(50, 500)),
        sf::RectangleShape(sf::Vector2f(50, -500)),
        sf::RectangleShape(sf::Vector2f(50, 500))
    };
    obstacles4[0].setFillColor(sf::Color::Red);
    obstacles4[0].setPosition(200, 100);
    obstacles4[1].setFillColor(sf::Color::Red);
    obstacles4[1].setPosition(400, 500);
    obstacles4[2].setFillColor(sf::Color::Red);
    obstacles4[2].setPosition(600, 100);

    sf::RectangleShape endPoint4(sf::Vector2f(50, 50));
    endPoint4.setFillColor(sf::Color::Yellow);
    endPoint4.setPosition(WINDOW_WIDTH - 70, WINDOW_HEIGHT / 2);

    std::vector<Enemy> enemies4 = {
        Enemy(0, 600 ),

    };

    std::vector<VerticalEnemy> verticalEnemies4 = {
        VerticalEnemy(250, 400, 0.1f),
        VerticalEnemy(450, 100, -0.1f),
        VerticalEnemy(250, 100, 0.1f),
        VerticalEnemy(450, 400, -0.1f)
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!gameRunning && event.type == sf::Event::MouseButtonPressed) {
                if (menu.startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    gameRunning = true;
                    currentLevel = 0;
                    player.shape.setPosition(50, WINDOW_HEIGHT / 2);
                }
                if (menu.exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                }
            }
            if (gameRunning && event.type == sf::Event::KeyPressed) {
                if (currentLevel == 0) player.move(event.key.code, obstacles0);
                else if (currentLevel == 1) player.move(event.key.code, obstacles1);
                else if (currentLevel == 2) player.move(event.key.code, obstacles2);
                else if (currentLevel == 3) player.move(event.key.code, obstacles3);
                else if (currentLevel == 4) player.move(event.key.code, obstacles4);
            }
        }
        if (gameRunning && currentLevel == 0 && player.shape.getGlobalBounds().intersects(endPoint0.getGlobalBounds())) {
            std::cout << "Przechodzisz do poziomu 2!" << std::endl;
            currentLevel = 1;
            player.shape.setPosition(50, WINDOW_HEIGHT / 2);
        }
        if (gameRunning && currentLevel == 1 && player.shape.getGlobalBounds().intersects(endPoint1.getGlobalBounds())) {
            std::cout << "Przechodzisz do poziomu 3!" << std::endl;
            currentLevel = 2;
            player.shape.setPosition(50, WINDOW_HEIGHT / 2);
        }
        if (gameRunning && currentLevel == 2 && player.shape.getGlobalBounds().intersects(endPoint2.getGlobalBounds())) {
            std::cout << "Przechodzisz do poziomu 4!" << std::endl;
            currentLevel = 3;
            player.shape.setPosition(50, WINDOW_HEIGHT / 2);
        }
        if (gameRunning && currentLevel == 3 && player.shape.getGlobalBounds().intersects(endPoint3.getGlobalBounds())) {
            std::cout << "Przechodzisz do poziomu 5!" << std::endl;
            currentLevel = 4;
            player.shape.setPosition(50, WINDOW_HEIGHT / 2);
        }
        if (gameRunning && currentLevel == 4 && player.shape.getGlobalBounds().intersects(endPoint4.getGlobalBounds())) {
            std::cout << "Ukończyłeś grę!" << std::endl;
            gameRunning = false;
 
            float elapsedTime = gameClock.getElapsedTime().asSeconds();
            timeText.setString("Twój czas gry: " + std::to_string(elapsedTime) + " sekund");
        }

        if (gameRunning && currentLevel == 2) {
            for (auto& enemy : enemies2) {
                enemy.chase(player.shape.getPosition(), obstacles2);
                if (player.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
                    std::cout << "Gracz został złapany! Restart poziomu 3." << std::endl;
                    resetPositions(player, enemies2, verticalEnemies3);
                }
            }
            
        }
        if (gameRunning && currentLevel == 3) {
            for (auto& enemy : enemies3) {
                enemy.chase(player.shape.getPosition(), obstacles3);
                if (player.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
                    std::cout << "Gracz został złapany! Restart poziomu 4." << std::endl;
                    resetPositions(player, enemies3, verticalEnemies3);
                }
            }
            for (auto& verticalEnemy : verticalEnemies3) {
                verticalEnemy.move();
                if (player.shape.getGlobalBounds().intersects(verticalEnemy.shape.getGlobalBounds())) {
                    std::cout << "Gracz został trafiony przez pionowego przeciwnika! Restart poziomu 4." << std::endl;
                    resetPositions(player, enemies3, verticalEnemies3);
                }
            }
        }
        if (gameRunning && currentLevel == 4) {
            for (auto& enemy : enemies4) {
                enemy.chase(player.shape.getPosition(), obstacles4);
                if (player.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
                    std::cout << "Gracz został złapany! Restart poziomu 5." << std::endl;
                    resetPositions(player, enemies4, verticalEnemies4);
                }
            }
            for (auto& verticalEnemy : verticalEnemies4) {
                verticalEnemy.move();
                if (player.shape.getGlobalBounds().intersects(verticalEnemy.shape.getGlobalBounds())) {
                    std::cout << "Gracz został trafiony przez pionowego przeciwnika! Restart poziomu 5." << std::endl;
                    resetPositions(player, enemies4, verticalEnemies4);
                }
            }
        }

        window.clear();
        if (!gameRunning) {
            window.draw(menu.title);
            window.draw(menu.startButton);
            window.draw(menu.exitButton);
        }
        else {
            window.draw(player.shape);
            if (currentLevel == 0) {
                window.draw(endPoint0);
                for (const auto& obstacle : obstacles0) window.draw(obstacle);
            }
            else if (currentLevel == 1) {
                window.draw(endPoint1);
                for (const auto& obstacle : obstacles1) window.draw(obstacle);
            }
            else if (currentLevel == 2) {
                window.draw(endPoint2);
                for (const auto& obstacle : obstacles2) window.draw(obstacle);
                for (const auto& enemy : enemies2) window.draw(enemy.shape);
            }
            else if (currentLevel == 3) {
                window.draw(endPoint3);
                for (const auto& obstacle : obstacles3) window.draw(obstacle);
                for (const auto& enemy : enemies3) window.draw(enemy.shape);
                for (const auto& verticalEnemy : verticalEnemies3) window.draw(verticalEnemy.shape);
            }
            else if (currentLevel == 4) {
                window.draw(endPoint4);
                for (const auto& obstacle : obstacles4) window.draw(obstacle);
                for (const auto& enemy : enemies4) window.draw(enemy.shape);
                for (const auto& verticalEnemy : verticalEnemies4) window.draw(verticalEnemy.shape);
            }
        }
        window.display();
    }

    return 0;
}
