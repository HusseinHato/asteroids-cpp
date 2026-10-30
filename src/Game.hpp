#pragma once

#include "Bullet.hpp"
#include "Ship.hpp"
#include <SFML/Graphics.hpp>

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
  Bullet m_bullet{{200.f, 200.f}, {0.f, 0.f}};
};
