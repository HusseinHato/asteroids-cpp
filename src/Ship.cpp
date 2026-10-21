#include "Ship.hpp"
#include "Config.hpp"
#include <cmath>

Ship::Ship() {
  m_shape.setPointCount(3);
  m_shape.setPoint(0, sf::Vector2f(0.f, -20.f));  // Hidung kapal
  m_shape.setPoint(1, sf::Vector2f(-12.f, 15.f)); // Sayap kiri
  m_shape.setPoint(2, sf::Vector2f(12.f, 15.f));  // Sayap kanan

  m_shape.setFillColor(sf::Color::Transparent);
  m_shape.setOutlineColor(sf::Color::White);
  m_shape.setOutlineThickness(2.f);

  setPosition(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f);
}

void Ship::handleInput(sf::Time dt) {
  const float dtSeconds = dt.asSeconds();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    rotate(-m_rotationSpeed * dtSeconds);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    rotate(m_rotationSpeed * dtSeconds);
  }

  const float radians = getRotation() * (Config::PI / 180.f);
  const sf::Vector2f direction(std::sin(radians), -std::cos(radians));

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    m_velocity += direction * m_acceleration * dtSeconds;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    m_velocity -= direction * m_acceleration * dtSeconds;
  }
}

void Ship::update(sf::Time dt) {
  const float dtSeconds = dt.asSeconds();

  m_velocity *= m_dragCoefficient;
  move(m_velocity * dtSeconds);

  wrapAroundScreen();
}

void Ship::wrapAroundScreen() {
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

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_shape, states);
}
