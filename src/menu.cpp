#include "menu.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "resource-holder.hpp"
#include "resource-declarations.hpp"

Menu::Menu(sf::Texture & bg, FontHolder &) :
  bg_{ bg }
{
  bg_.setScale(0.5f, 0.5f);
}

Menu::Menu(FontHolder &) :
  bg_{ }
{ }

void Menu::setBackground(sf::Texture & bg)
{
  bg_.setTexture(bg);
  bg_.setScale(0.5f, 0.5f);
}
void Menu::render(sf::RenderWindow & window) const
{
  window.draw(bg_);
}
