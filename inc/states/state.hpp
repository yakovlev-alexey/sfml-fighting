#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include <SFML/System/NonCopyable.hpp>

#include "state-declarations.hpp"
#include "../resource-declarations.hpp"

namespace sf
{
  class Time;
  class Event;
  class RenderWindow;
}

class State : public sf::NonCopyable
{
public:

  struct context_t
  {
    sf::RenderWindow & window;
    TextureHolder & textures;
    FontHolder & fonts;
  };

  typedef std::unique_ptr<State> Pointer;

  State(const context_t & context);

  virtual void handleEvent(const sf::Event & event) = 0;
  virtual void update(const sf::Time & dt) = 0;
  virtual void render() const = 0;

  virtual States::ID getStateId() const = 0;

protected:

  context_t context_;
};

#endif
