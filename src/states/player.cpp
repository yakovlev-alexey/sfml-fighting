#include <states/player.hpp>

#include <cmath>
#include <iostream>
#include <stdexcept>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <util/lerp.hpp>
#include <resource-holder.hpp>
#include <resource-declarations.hpp>

Player::Player(TextureHolder & textures) :
  Character{ },
  actions_{ }
{ 
  try {
    sprites_.idle = &textures.getOrLoad(Textures::PlayerIdle, "data/textures/player-idle.png");
    character_.setTexture(*sprites_.idle);
    character_.setScale(2.0f, 2.0f);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.move = &textures.getOrLoad(Textures::PlayerMove, "data/textures/player-move.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.jump = &textures.getOrLoad(Textures::PlayerJump, "data/textures/player-jump.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.attack = &textures.getOrLoad(Textures::PlayerAttack, "data/textures/player-attack.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sprites_.hit = &textures.getOrLoad(Textures::PlayerHit, "data/textures/player-hit.png");
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

void Player::update(const sf::Time & dt)
{
  if (state_ == State::Hit && hitClock_.getElapsedTime().asSeconds() > HIT_DURATION) {
    state_ = State::Idle;
  }

  float dts = dt.asSeconds(); 

  if (state_ == State::Hit) {
    while (!actions_.empty()) {
      actions_.pop_front();
    }

    velocity_.x = util::lerp(velocity_.x, 0, dts * ACCELERATION);
    velocity_.y = util::lerp(velocity_.y, DOWNFORCE, dts);

    return;
  }

  if (state_ == State::Attack && attackClock_.getElapsedTime().asSeconds() > ATTACK_DURATION) {
    state_ = State::Idle;
  }

  bool attack = (state_ == State::Attack);

  while (!actions_.empty()) {
    Action action = actions_.front();
    switch (action) {
      case Action::MoveLeft:
        velocity_.x = util::lerp(velocity_.x, -MOVEMENT_SPEED, dts * ACCELERATION);
        break;
      case Action::MoveRight:
        velocity_.x = util::lerp(velocity_.x, MOVEMENT_SPEED, dts * ACCELERATION);
        break;
      case Action::Jump:
        velocity_.y = JUMPFORCE;
        break;
      case Action::Attack:
        if (!attack) {
          attackClock_.restart();
          attack = true;
        }
        break;
      default:
        break;
    }
    actions_.pop_front();
  }

  velocity_.x = util::lerp(velocity_.x, 0, dts * ACCELERATION);
  velocity_.y = util::lerp(velocity_.y, DOWNFORCE, dts);

  float idleError = 1e-2f;


  if (attack) {
    state_ = State::Attack;
  } else if (velocity_.y < 0.0f) {
    state_ = State::Jump;
  } else if (std::abs(velocity_.x) > idleError) {
    state_ = State::Move;
  } else {
    state_ = State::Idle;
  }

  sf::IntRect tr = character_.getTextureRect();

  sf::Texture * tx = getTexture();
  if (tx) {
    character_.setTexture(*tx);
    sf::Vector2u size = tx->getSize();
    tr.width = (tr.width > 0) ? size.x : -size.x;
    tr.left = (tr.left == 0) ? 0 : size.x;
    tr.height = size.y;
    character_.setTextureRect(tr);
  }

  if (velocity_.x < 0.0f && direction_ == Direction::Right) { 
    direction_ = Direction::Left;
    character_.setTextureRect({ tr.width, 0, -tr.width, tr.height });
  } else if (velocity_.x >= 0.0f && direction_ == Direction::Left) {
    direction_ = Direction::Right;
    character_.setTextureRect({ 0, 0, tr.left, tr.height });
  }
}
  