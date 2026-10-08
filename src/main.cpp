#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // 1. Create the window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Asteroids - Phase 1: Game Loop & Windowing");
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
    ship.setPosition(512.f, 384.f);

    float rotationSpeed = 200.f; // degrees per second

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
        }

        // --- 3. Render Phase ---
        window.clear(sf::Color(15, 15, 25)); // Deep space dark blue/black
        window.draw(ship);
        window.display();
    }

    return 0;
}
