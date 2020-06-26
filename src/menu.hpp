#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "button.hpp"
#include "container.hpp"
#include "resource-declarations.hpp"

namespace sf
{
  class Event;
  class Texture;
  class RenderWindow;
}

class Menu : public sf::NonCopyable
{
public:
  Menu(TextureHolder & textures, FontHolder & fonts);

  void handleEvent(const sf::Event & event);
  void render(sf::RenderWindow & window) const;

private:
  sf::Sprite logo_;
  GUI::Container btnContainer_;
  sf::Sprite bg_;
};

#endif
