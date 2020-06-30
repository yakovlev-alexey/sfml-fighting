#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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
  void handleInteraction(Character & char1, Character & char2) const;

  void updateHbars();
  void updateTimer();

  static const float FLOOR_HEIGHT;

  static const float HBAR_HEIGHT;

  sf::Vector2u screenSize_;

  Player player_;
  Opponent opponent_;

  sf::Sprite bg_;

  float hbarWidth_;
  sf::RectangleShape playerHbar_;
  sf::RectangleShape opponentHbar_;

  sf::Text playerTxt_;
  sf::Text opponentTxt_;

  sf::Text timer_;
  sf::Clock clock_;
};

#endif
