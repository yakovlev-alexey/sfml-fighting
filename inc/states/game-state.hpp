#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <states/world.hpp>
#include <states/state.hpp>
#include <resource-declarations.hpp>

namespace sf
{
  class Time;
  class RenderWindow;
}

class GameState : public State
{
public:
  GameState(const context_t & context);

  void handleEvent(const sf::Event & event) override;
  void update(const sf::Time & dt) override;
  void render() const override;

  States::ID getStateId() const override;

private:

  World world_;
  // TODO
};


#endif
