#pragma once

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

class Game {
public:
  Game();

  void run();

private:
  void processEvents();
  void update(sf::Time dt);
  void render();

  sf::RenderWindow m_window;
  Ship m_ship;
};
