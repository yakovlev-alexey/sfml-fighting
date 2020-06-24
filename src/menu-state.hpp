#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "menu.hpp"
#include "state.hpp"
#include "resource-declarations.hpp"

namespace sf
{
  class RenderWindow;
}

class MenuState : public State
{
public:
  MenuState(sf::RenderWindow & window, TextureHolder & textures, FontHolder & fonts);

  // Handles an event. Returns false if the handling of an event lead to a state change
  bool handleEvent(const sf::Event & event) override;
  // Handles update logic. Returns false if the handling of an update lead to a state change
  bool update() override;
  // Renders the current Game State
  void render() override;

private:
  sf::RenderWindow & window_;
  TextureHolder & textures_;
  FontHolder & fonts_;  
  Menu menu_;
};


#endif
