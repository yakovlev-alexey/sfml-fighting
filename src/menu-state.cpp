#include "menu-state.hpp"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "state.hpp"
#include "resource-holder.hpp"
#include "resource-declarations.hpp"

MenuState::MenuState(sf::RenderWindow & window, TextureHolder & textures, FontHolder & fonts) :
  window_{ window },
  textures_{ textures },
  fonts_{ fonts },
  bg_{ }
{ 
  try {
    bg_.setTexture(textures.getOrLoad(Textures::Background, "data/textures/forest-background.png"));
    bg_.setScale(0.5f, 0.5f);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }
}

bool MenuState::update()
{
  return true;
}

bool MenuState::handleEvent(const sf::Event &)
{
  return true;
}

void MenuState::render()
{
  window_.clear();

  window_.draw(bg_);

  window_.display();
}

