#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <SFML/System/NonCopyable.hpp>

#include <states/state.hpp>
#include <states/state-declarations.hpp>

#include <resource-holder.hpp>
#include <resource-declarations.hpp>

namespace sf
{
  class Time;
}

class StateManager : public sf::NonCopyable
{
public:
  StateManager(const State::context_t & context);
  virtual ~StateManager();

  void processEvent(const sf::Event & event);
  void update(const sf::Time & dt);
  void render();

  State & getState();
  const State & getState() const;
  States::ID getStateId() const;

  void queueChange(States::ID state);

  static StateManager & getInstance();

private:

  static StateManager * instance;
  
  State::context_t context_;
  std::unique_ptr<State> state_;
  States::ID queued_;
};

#endif
