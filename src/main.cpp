#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

constexpr float PI = 3.14159265f;
constexpr unsigned int WINDOW_WIDTH = 1024;
constexpr unsigned int WINDOW_HEIGHT = 768;

int main() {
    // 1. Create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids - Phase 1: Game Loop & Windowing");
    window.setVerticalSyncEnabled(true);

    // 2. Setup fixed timestep timing (Key Learning 1)
    const sf::Time TIME_PER_FRAME = sf::seconds(1.0f / 60.0f); // 60 updates per second
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // Temporary test entity: Simple ship represented as a triangle
    sf::ConvexShape ship;
    ship.setPointCount(3);
    ship.setPoint(0, sf::Vector2f(0.f, -20.f));   // Nose
    ship.setPoint(1, sf::Vector2f(-12.f, 15.f));  // Left wing
    ship.setPoint(2, sf::Vector2f(12.f, 15.f));   // Right wing
    ship.setFillColor(sf::Color::Transparent);
    ship.setOutlineColor(sf::Color::White);
    ship.setOutlineThickness(2.f);
    ship.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

    float rotationSpeed = 200.f; // degrees per second
    float acceleration = 200.f;
    float drag_coefficient = 0.99f;
    
    sf::Vector2f velocity(0.f, 0.f);

    // Main Game Loop
    while (window.isOpen()) {
        // --- 1. Event Polling (Window events & Edge-triggered inputs) ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // --- 2. Fixed Timestep Accumulator ---
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;

            // --- Fixed Physics/Logic Update (60 FPS constant) ---
            float dtSeconds = TIME_PER_FRAME.asSeconds();

            // Continuous input polling for smooth movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                ship.rotate(-rotationSpeed * dtSeconds);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                ship.rotate(rotationSpeed * dtSeconds);
            }

            float radians = ship.getRotation() * (PI / 180.f);
            float dirX = std::sin(radians);
            float dirY = -std::cos(radians);
            sf::Vector2f direction(dirX, dirY);
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                velocity += direction * acceleration * dtSeconds;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                velocity -= direction * acceleration * dtSeconds;
            }

            velocity *= drag_coefficient;
            ship.move(velocity * dtSeconds);

            sf::Vector2f pos = ship.getPosition();
            if (pos.x < 0.f) pos.x = static_cast<float>(WINDOW_WIDTH);
            if (pos.x > WINDOW_WIDTH) pos.x = 0.f;
            if (pos.y < 0.f) pos.y = static_cast<float>(WINDOW_HEIGHT);
            if (pos.y > WINDOW_HEIGHT) pos.y = 0.f;
            ship.setPosition(pos);
        }

        // --- 3. Render Phase ---
        window.clear(sf::Color(15, 15, 25)); // Deep space dark blue/black
        window.draw(ship);
        window.display();
    }

    return 0;
}
