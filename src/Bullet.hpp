#pragma once

#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable, public sf::Transformable {
public:
  Bullet(sf::Vector2f position, sf::Vector2f velocity);

  void update(sf::Time dt);

  bool isExpired() const;

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  void wrapAroundScreen();

  sf::CircleShape m_shape;
  sf::Vector2f m_velocity;

  sf::Time m_remainingLifetime{sf::seconds(1.f)};
};