#include "Game.hpp"
#include "Config.hpp"

Game::Game()
    : m_window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT),
               "Asteroids - Phase 1: Game Loop & Windowing") {
  m_window.setVerticalSyncEnabled(true);
}

void Game::run() {
  const sf::Time timePerFrame = sf::seconds(1.0f / Config::UPDATES_PER_SECOND);
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (m_window.isOpen()) {
    processEvents();
    timeSinceLastUpdate += clock.restart();

    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      processEvents();
      update(timePerFrame);
    }

    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    }
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
      m_window.close();
    }
  }
}

void Game::update(sf::Time dt) {
  m_ship.handleInput(dt);
  m_ship.update(dt);
}

void Game::render() {
  m_window.clear(sf::Color(15, 15, 25)); // Deep space dark blue/black
  m_window.draw(m_ship);
  m_window.display();
}
