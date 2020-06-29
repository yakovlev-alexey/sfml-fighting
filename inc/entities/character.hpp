#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <list>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sf
{
  class Time;
  class Event;
  class Texture;
  class RenderTarget;
  class RenderStates;
}

class Character : public sf::Transformable, public sf::Drawable
{
public:

  enum class State
  {
    Idle,
    Move,
    Jump,
    Attack,
    Hit,
    Dead
  };

  enum class Direction
  {
    Left,
    Right
  };

  Character();
  virtual ~Character() = default;

  sf::FloatRect getBounds() const;

  State getState() const;
  void setState(State state);

  float getHealth() const;
  void damage(float damage, Direction direction);
  float getDamage() const;

  bool isDead() const;

  bool getGrounded() const;
  void setGrounded(bool grounded);

  void moveVelocity();
  void reset();

  virtual void handleEvent(const sf::Event & event) = 0;
  virtual void update(const sf::Time & dt);
  
protected:

  enum class Action
  {
    None,
    MoveLeft,
    MoveRight,
    Jump,
    Attack
  };

  void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

  sf::Texture * getTexture() const;
  void updateTexture();

  static const float DOWNFORCE;
  static const float DOWNFORCE_ACCELERATION;
  static const float JUMPFORCE;

  static const float MOVEMENT_SPEED;
  static const float ACCELERATION;
  
  static const float HIT_DURATION;
  static const float ATTACK_DURATION;
  static const float ATTACK_COOLDOWN;

  static const float MAX_HEALTH;
  static const float DAMAGE;
  static const float DEATH_DURATION;

  static const float HIT_FORCE;
  static const float HIT_FORCE_UP;

  float health_;

  sf::Clock hitClock_;
  sf::Clock deathClock_;
  sf::Clock attackClock_;

  sf::Sprite character_;
  sf::Vector2f velocity_;

  std::list<Action> actions_;

  State state_;
  Direction direction_;

  bool isGrounded_;

  struct {
    sf::Texture * idle;
    sf::Texture * move;
    sf::Texture * jump;
    sf::Texture * attack;
    sf::Texture * hit;
    sf::Texture * dead;
  } sprites_;
};

#endif
