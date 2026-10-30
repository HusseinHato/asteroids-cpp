#include "Bullet.hpp"
#include "Config.hpp"
#include "SFML/Graphics/Color.hpp"
#include <cmath>

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
    : m_velocity(velocity) {

  m_shape.setRadius(Config::BULLET_RADIUS);
  m_shape.setOrigin(Config::BULLET_RADIUS, Config::BULLET_RADIUS);
  m_shape.setFillColor(sf::Color::White);

  setPosition(position);
}

// void Bullet::update(sf::Time dt) {
//   const float dtSeconds = dt.asSeconds();

//   move(m_velocity * dtSeconds);

//   wrapAroundScreen();
// }

void Bullet::wrapAroundScreen() {
  sf::Vector2f pos = getPosition();

  if (pos.x < 0.f)
    pos.x = static_cast<float>(Config::WINDOW_WIDTH);
  else if (pos.x > Config::WINDOW_WIDTH)
    pos.x = 0.f;

  if (pos.y < 0.f)
    pos.y = static_cast<float>(Config::WINDOW_HEIGHT);
  else if (pos.y > Config::WINDOW_HEIGHT)
    pos.y = 0.f;

  setPosition(pos);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_shape, states);
}
