#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <entities/character.hpp>
#include <resource-declarations.hpp>

namespace sf
{
  class Time;
  class Event;
}

class Player : public Character
{
public:
  Player(TextureHolder & textures);

  void handleEvent(const sf::Event & event) override;
};

#endif
