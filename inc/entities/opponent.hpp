#ifndef OPPONENT_HPP
#define OPPONENT_HPP

#include <SFML/System/Time.hpp>

#include <entities/character.hpp>
#include <resource-declarations.hpp>

class Player;

namespace sf
{
  class Time;
  class Event;
}

class Opponent : public Character
{
public:
  Opponent(TextureHolder & textures, Player & player);

  void handleEvent(const sf::Event & event) override;
  void update(const sf::Time & dt) override;
private:

  static const float ATTACK_OPPONENT_COOLDOWN;

  const Player & player_;
};

#endif
