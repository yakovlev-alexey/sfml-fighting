#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

namespace sf
{
  class Event;
}

class State
{
public:

  typedef std::unique_ptr<State> Pointer;

  // Handles an event. Returns false if the handling of an event lead to a state change
  virtual bool handleEvent(const sf::Event & event) = 0;
  // Handles update logic. Returns false if the handling of an update lead to a state change
  virtual bool update() = 0;
  // Renders the current Game State
  virtual void render() = 0;
};

#endif
