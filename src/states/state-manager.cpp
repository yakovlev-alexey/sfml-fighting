#include <states/state-manager.hpp>

#include <stdexcept>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <states/state.hpp>
#include <states/game-state.hpp>
#include <states/menu-state.hpp>
#include <resource-holder.hpp>

StateManager * StateManager::instance = nullptr;

StateManager::StateManager(const State::context_t & context) :
  context_{ context },
  state_{ nullptr }
{ 
  if (StateManager::instance != nullptr) {
    throw std::runtime_error{ "StateManager::StateManager() : only one instance of StateManager can be present at once" };
  }

  StateManager::instance = this;

  state_ = std::make_unique<MenuState>(context);
}

StateManager::~StateManager()
{
  StateManager::instance = nullptr;
}

void StateManager::processEvent(const sf::Event & event)
{
  state_->handleEvent(event);
}

void StateManager::update(const sf::Time & dt)
{
  state_->update(dt);
}

void StateManager::render()
{
  if (queued_ != States::None) {
    switch (queued_) {
      case States::Menu:
        state_ = std::make_unique<MenuState>(context_);
        break;
      case States::Game:
        state_ = std::make_unique<GameState>(context_);
        break;
      case States::Exit:
        context_.window.close();
        break;
      default:
        // TODO
        break;
    }
    queued_ = States::None;
  }
  state_->render();
}

State & StateManager::getState()
{
  return *state_;
}

const State & StateManager::getState() const
{
  return *state_;
}

States::ID StateManager::getStateId() const
{
  return state_->getStateId();
}

void StateManager::queueChange(States::ID state)
{
  queued_ = state;
}

StateManager & StateManager::getInstance()
{
  return *StateManager::instance;
}