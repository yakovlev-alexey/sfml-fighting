#include <entities/character.hpp>

#include <list>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <util/lerp.hpp>
#include <util/random.hpp>

const float Character::DOWNFORCE = 10.0f;
const float Character::DOWNFORCE_ACCELERATION = 4.0f;
const float Character::JUMPFORCE = -20.0f;

const float Character::MOVEMENT_SPEED = 15.0f;
const float Character::ACCELERATION = 6.0f;

const float Character::HIT_DURATION = 0.5f;
const float Character::ATTACK_DURATION = 0.3f;
const float Character::ATTACK_COOLDOWN = 0.9f;
const float Character::ATTACK_FALLOFF = 0.25f;

const float Character::MAX_HEALTH = 100.0f;
const float Character::DEATH_DURATION = 1.5f;

const float Character::MIN_DAMAGE = 5.0f;
const float Character::MAX_DAMAGE = 7.75f;
const float Character::FALLING_MODIFIER = 1.35f;
const float Character::FALLING_THRESHOLD = 0.5f;

const float Character::HIT_FORCE = 6.0f;
const float Character::HIT_FORCE_UP = -4.0f;

Character::Character() :
  Transformable{ },
  health_{ MAX_HEALTH },
  hitClock_{ },
  attackClock_{ },
  damageModifier_{ 1.0f },
  character_{ },
  velocity_{ 0.0f, 0.0f },
  actions_{ },
  state_{ State::Idle },
  direction_{ Direction::Right },
  isGrounded_{ false },
  sprites_{
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr
  }
{ }

sf::FloatRect Character::getBounds() const
{
  sf::FloatRect bb = character_.getLocalBounds();
  return sf::FloatRect(getPosition(), { 100, bb.height });
}

Character::State Character::getState() const
{
  return state_;
}

void Character::setState(State state)
{
  state_ = state;
  if (state == State::Dead) {
    deathClock_.restart();
  } else if (state == State::Hit) {
    hitClock_.restart();
    character_.setColor(sf::Color(255, 255, 255, 200));
  } else if (state == State::Attack) {
    attackClock_.restart();
  }
}

float Character::getHealth() const
{
  return (health_ < 0.0f) ? 0.0f : health_;
}

float Character::getMaxHealth()
{
  return MAX_HEALTH;
}

void Character::damage(float damage, Direction direction)
{
  if (state_ == State::Hit) {
    return;
  }

  health_ -= damage;

  if (health_ <= 0.0f) {
    setState(State::Dead);
    return;
  }

  velocity_.x = (direction == Direction::Right) ? HIT_FORCE : -HIT_FORCE;
  velocity_.y = HIT_FORCE_UP;
  setState(State::Hit);
}

float Character::getDamage() const
{
  util::FloatGenerator floatGen = { };

  float damage = floatGen.get(MIN_DAMAGE, MAX_DAMAGE);

  // Increased damage when falling
  if (!isGrounded_ && velocity_.y > FALLING_THRESHOLD) {
    damage *= FALLING_MODIFIER;
  }

  // Spamming attacks leads to smaller damage
  if (damageModifier_ < 1.0f) {
    damage *= damageModifier_;
  }

  return damage;
}

bool Character::isDead() const
{
  return (health_ < 0) && (deathClock_.getElapsedTime().asSeconds() > DEATH_DURATION);
}

bool Character::getGrounded() const
{
  return isGrounded_;
}

void Character::setGrounded(bool grounded)
{
  isGrounded_ = grounded;
}

void Character::moveVelocity()
{
  move(velocity_);
}

void Character::reset()
{
  move(-velocity_);
}

void Character::update(const sf::Time & dt)
{
  if (state_ == State::Hit && isGrounded_ && hitClock_.getElapsedTime().asSeconds() > HIT_DURATION) {
    state_ = State::Idle;
    character_.setColor(sf::Color(255, 255, 255, 255));
    velocity_.x = -velocity_.x;
  }

  float dts = dt.asSeconds(); 

  if (state_ == State::Hit || state_ == State::Dead) {
    actions_ = std::list<Action>();

    updatePhysics(dts);

    updateTexture();

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
        if (isGrounded_) {
          velocity_.y = JUMPFORCE;
        }
        break;
      case Action::Attack:
        if (!attack && attackClock_.getElapsedTime().asSeconds() > ATTACK_COOLDOWN) {
          damageModifier_ = (attackClock_.restart().asSeconds()
              - ATTACK_COOLDOWN) / ATTACK_FALLOFF;
          attack = true;
        }
        break;
      default:
        break;
    }
    actions_.pop_front();
  }

  updatePhysics(dts);

  float idleError = 1e-2f;

  if (attack) {
    state_ = State::Attack;
  } else if (!isGrounded_) {
    state_ = State::Jump;
  } else if (std::abs(velocity_.x) > idleError) {
    state_ = State::Move;
  } else {
    state_ = State::Idle;
  }

  updateTexture();
}
  
void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  target.draw(character_, states);
}

sf::Texture * Character::getTexture() const
{
  if (state_ == State::Dead) {
    return sprites_.dead;
  } else if (state_ == State::Hit) {
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

void Character::updateTexture()
{
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

void Character::updatePhysics(float dts)
{
  velocity_.x = util::lerp(velocity_.x, 0, dts * ACCELERATION);
  velocity_.y = util::lerp(velocity_.y, DOWNFORCE, dts * DOWNFORCE_ACCELERATION);
}
