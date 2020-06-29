#include <entities/opponent.hpp>

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <entities/player.hpp>
#include <resource-holder.hpp>
#include <resource-declarations.hpp>

Opponent::Opponent(TextureHolder & textures, Player & player) :
  Character{ },
  player_{ player }
{
  try {
    sprites_.idle = &textures.getOrLoad(Textures::OpponentIdle, "data/textures/opponent/idle.png");
    character_.setTexture(*sprites_.idle);
    character_.setScale(2.0f, 2.0f);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.move = &textures.getOrLoad(Textures::OpponentMove, "data/textures/opponent/move.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.jump = &textures.getOrLoad(Textures::OpponentJump, "data/textures/opponent/jump.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.attack = &textures.getOrLoad(Textures::OpponentAttack, "data/textures/opponent/attack.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.hit = &textures.getOrLoad(Textures::OpponentHit, "data/textures/opponent/hit.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }
}

void Opponent::handleEvent(const sf::Event &)
{ }

void Opponent::update(const sf::Time & dt)
{
  // TODO: queue actions
  Character::update(dt);
}
