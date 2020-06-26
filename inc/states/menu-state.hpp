#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "menu.hpp"
#include "state.hpp"
#include "state-declarations.hpp"
#include "../resource-declarations.hpp"

namespace sf
{
  class Time;
  class RenderWindow;
}

class MenuState : public State
{
public:
  MenuState(const context_t & context);

  void handleEvent(const sf::Event & event) override;
  void update(const sf::Time & dt) override;
  void render() const override;

  States::ID getStateId() const override;

private:
  Menu menu_;
};


#endif
