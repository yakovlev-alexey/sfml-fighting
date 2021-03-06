#include <gui/container.hpp>

#include <memory>
#include <vector>
#include <stdexcept>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <gui/button.hpp>

GUI::Container::Container() :
  selected_{ 0 },
  btns_{ }
{ }

void GUI::Container::add(std::unique_ptr<Button> & btn)
{
  if (!btn) {
    throw std::invalid_argument{ "Container::add : button can not be nullptr" };
  }
  if (btns_.empty()) {
    btn->select();
  }
  btns_.push_back(std::move(btn));
}

void GUI::Container::handleEvent(const sf::Event & event)
{
  if (event.type == sf::Event::KeyReleased) {
    if ((selected_ < btns_.size() - 1) && ((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S))) {
      btns_[selected_]->deselect();
      btns_[++selected_]->select();
    } 
    if ((selected_ > 0) && ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::W))) {
      btns_[selected_]->deselect();
      btns_[--selected_]->select();
    }
    if ((event.key.code == sf::Keyboard::Enter) || (event.key.code == sf::Keyboard::Space)) {
      btns_[selected_]->activate();
    }
  }
}

void GUI::Container::render(sf::RenderWindow & window) const
{
  size_t size = btns_.size();
  for (size_t i = 0u; i < size; ++i) {
    window.draw(*btns_[i]);
  }
}
