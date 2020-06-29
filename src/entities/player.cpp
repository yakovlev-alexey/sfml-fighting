#include <entities/player.hpp>

#include <cmath>
#include <iostream>
#include <stdexcept>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <resource-holder.hpp>
#include <resource-declarations.hpp>

Player::Player(TextureHolder & textures) :
  Character{ }
{ 
  try {
    sprites_.idle = &textures.getOrLoad(Textures::PlayerIdle, "data/textures/player/idle.png");
    character_.setTexture(*sprites_.idle);
    character_.setScale(2.0f, 2.0f);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.move = &textures.getOrLoad(Textures::PlayerMove, "data/textures/player/move.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.jump = &textures.getOrLoad(Textures::PlayerJump, "data/textures/player/jump.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.attack = &textures.getOrLoad(Textures::PlayerAttack, "data/textures/player/attack.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.hit = &textures.getOrLoad(Textures::PlayerHit, "data/textures/player/hit.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.dead = &textures.getOrLoad(Textures::PlayerDead, "data/textures/player/dead.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }
}

void Player::handleEvent(const sf::Event & event)
{
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::A) {
      actions_.push_back(Action::MoveLeft);
    } else if (event.key.code == sf::Keyboard::D) {
      actions_.push_back(Action::MoveRight);
    } else if (event.key.code == sf::Keyboard::J) {
      actions_.push_back(Action::Jump);
    } else if (event.key.code == sf::Keyboard::H) {
      actions_.push_back(Action::Attack);
    }
  }
}
