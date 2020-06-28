#include <states/game-state.hpp>

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <states/state.hpp>
#include <states/state-declarations.hpp>

#include <resource-holder.hpp>
#include <resource-declarations.hpp>

GameState::GameState(const context_t & context) :
  State{ context },
  world_{ context }
{ }

void GameState::handleEvent(const sf::Event & event)
{
  world_.handleEvent(event);
}


void GameState::update(const sf::Time & dt)
{
  world_.update(dt);
}

void GameState::render() const
{
  context_.window.clear();

  world_.render(context_.window);

  context_.window.display();
}

States::ID GameState::getStateId() const
{
  return States::Game;
}
