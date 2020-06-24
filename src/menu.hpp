#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "button.hpp"
#include "container.hpp"
#include "resource-declarations.hpp"

namespace sf
{
  class Texture;
  class RenderWindow;
}

class Menu
{
public:
  Menu(TextureHolder & bg, FontHolder & fonts);
  void render(sf::RenderWindow & window) const;
private:
  GUI::Button logo_;
  GUI::Container btnContainer_;
  sf::Sprite bg_;
};

#endif
