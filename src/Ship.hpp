#pragma once

#include <SFML/Graphics.hpp>

class Ship : public sf::Drawable, public sf::Transformable {
public:
  Ship();

  void handleInput(sf::Time dt);
  void update(sf::Time dt);

  const sf::Vector2f& getVelocity() const { return m_velocity; }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void wrapAroundScreen();

  sf::ConvexShape m_shape;
  sf::Vector2f m_velocity{0.f, 0.f};

  float m_rotationSpeed{200.f};    // degrees per second
  float m_acceleration{200.f};     // pixels per second^2
  float m_dragCoefficient{0.99f};  // friction per tick
};
