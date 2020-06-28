#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/Sprite.hpp>

#include <states/state.hpp>
#include <entities/player.hpp>
#include <entities/opponent.hpp>

namespace sf
{
  class Time;
  class Event;
  class RenderWindow;
}

class Character;

class World
{
public:
  World(const State::context_t & context);

  void handleEvent(const sf::Event & event);
  void update(const sf::Time & dt);
  void render(sf::RenderWindow & window) const;
  
private:

  void handlePhysics(Character & character) const;
  void handleCollisions(Character & character) const;

  static const float FLOOR_HEIGHT;

  sf::Vector2u screenSize_;

  Player player_;
  Opponent opponent_;
  sf::Sprite bg_;
};

#endif
