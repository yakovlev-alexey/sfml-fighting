#include <states/character.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

const float Character::DOWNFORCE = 4.0f;
const float Character::JUMPFORCE = -8.0f;

const float Character::MOVEMENT_SPEED = 10.0f;
const float Character::ACCELERATION = 8.0f;

const float Character::HIT_DURATION = 0.3f;
const float Character::ATTACK_DURATION = 0.5f;

Character::Character() :
  Transformable{ },
  hitClock_{ },
  attackClock_{ },
  character_{ },
  velocity_{ 0.0f, 0.0f },
  state_{ State::Idle },
  direction_{ Direction::Right },
  sprites_{
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr
  }
{
  setPosition(50.0f, 100.0f);
}

sf::FloatRect Character::getBounds() const
{
  sf::FloatRect bb = character_.getLocalBounds();
  return sf::FloatRect(getPosition(), { bb.width, bb.height });
}

Character::State Character::getState() const
{
  return state_;
}

void Character::setState(State state)
{
  state_ = state;
  if (state == State::Hit) {
    hitClock_.restart();
  }
}

void Character::moveVelocity()
{
  move(velocity_);
}

void Character::reset()
{
  move(-velocity_);
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  target.draw(character_, states);
}

sf::Texture * Character::getTexture() const
{
  if (state_ == State::Hit) {
    return sprites_.hit;
  } else if (state_ == State::Attack) {
    return sprites_.attack;
  } else if (state_ == State::Jump) {
    return sprites_.jump;
  } else if (state_ == State::Move) {
    return sprites_.move;
  } else {
    return sprites_.idle;
  }
}
