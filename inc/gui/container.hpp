#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <memory>

#include "button.hpp"

namespace sf
{
  class Event;
  class RenderWindow;
}

namespace GUI
{

  class Container
  {
  public:
    Container();

    void add(std::unique_ptr<Button> & btn);
    void handleEvent(const sf::Event & event);
    void render(sf::RenderWindow & window) const;
    
  private:
    size_t selected_;
    std::vector<std::unique_ptr<Button>> btns_;
  };

}

#endif
