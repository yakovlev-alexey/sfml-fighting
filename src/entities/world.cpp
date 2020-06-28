#include <entities/world.hpp>

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <resource-holder.hpp>
#include <entities/character.hpp>
#include <resource-declarations.hpp>

const float World::FLOOR_HEIGHT = 80.0f;

World::World(const State::context_t & context) :
  screenSize_{ context.window.getSize() },
  player_{ context.textures },
  bg_{ }
{
  try {
    bg_.setTexture(context.textures.getOrLoad(Textures::Background, "data/textures/forest-background.png"));
    bg_.setScale(0.5f, 0.5f);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }
}

void World::handleEvent(const sf::Event & event)
{
  player_.handleEvent(event);
}

void World::update(const sf::Time & dt)
{
  player_.update(dt);

  player_.moveVelocity();

  handleCollisions(player_);

}

void World::render(sf::RenderWindow & window) const
{
  window.draw(bg_);
  window.draw(player_);
}

void World::handleCollisions(Character & character) const
{
  sf::FloatRect bb = character.getBounds();

  float bot = bb.top + bb.height;
  float floor = screenSize_.y - FLOOR_HEIGHT;
  if (bot > floor) {
    bb.top = floor - bb.height;
    character.setPosition(bb.left, bb.top);
  }

  if (bb.left < 0.0f) {
    character.setPosition(0.0f, bb.top);
  }

  float right = bb.left + bb.width;
  if (right > screenSize_.x) {
    character.setPosition(screenSize_.x - bb.width, bb.top);
  }
}
