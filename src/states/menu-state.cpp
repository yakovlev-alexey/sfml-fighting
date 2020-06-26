#include <states/menu-state.hpp>

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <states/state.hpp>
#include <resource-holder.hpp>
#include <resource-declarations.hpp>

MenuState::MenuState(const context_t & context) :
  State{ context },
  menu_{ context.textures, context.fonts }
{ }

void MenuState::handleEvent(const sf::Event & event)
{
  menu_.handleEvent(event);
}

void MenuState::update(const sf::Time &)
{

}

void MenuState::render() const
{
  context_.window.clear();

  menu_.render(context_.window);

  context_.window.display();
}

States::ID MenuState::getStateId() const
{
  return States::Menu;
}
