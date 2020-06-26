#include "game-state.hpp"

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "state.hpp"
#include "../resource-holder.hpp"
#include "../resource-declarations.hpp"

GameState::GameState(const context_t & context) :
  State{ context }
{ }

void GameState::update(const sf::Time &)
{
  
}

void GameState::handleEvent(const sf::Event &)
{

}

void GameState::render() const
{
  context_.window.clear();

  context_.window.display();
}

States::ID GameState::getStateId() const
{
  return States::Game;
}
