#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>

#include "resource-declarations.hpp"

namespace sf
{
  class Texture;
  class RenderWindow;
}

class Menu
{
public:
  Menu(sf::Texture & bg, FontHolder & fonts);
  Menu(FontHolder & fonts);
  void setBackground(sf::Texture & bg);
  void render(sf::RenderWindow & window) const;
private:
  sf::Sprite bg_;
};

#endif
