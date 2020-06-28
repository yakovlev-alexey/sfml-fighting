#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>

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

  enum class Action
  {
    None,
    MoveLeft,
    MoveRight,
    Jump,
    Attack
  };

  Player(TextureHolder & textures);

  void handleEvent(const sf::Event & event) override;
  void update(const sf::Time & dt) override;

private:

  std::list<Action> actions_;

};

#endif
