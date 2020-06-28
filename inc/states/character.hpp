#ifndef CHARACTER_HPP
#define CHARACTER_HPP

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
    Hit
  };

  enum class Direction
  {
    Left,
    Right
  };

  Character();

  sf::FloatRect getBounds() const;

  State getState() const;
  void setState(State state);

  void moveVelocity();
  void reset();

  virtual void handleEvent(const sf::Event & event) = 0;
  virtual void update(const sf::Time & dt) = 0;
  
protected:

  void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

  sf::Texture * getTexture() const;

  static const float DOWNFORCE;
  static const float JUMPFORCE;

  static const float MOVEMENT_SPEED;
  static const float ACCELERATION;
  
  static const float HIT_DURATION;
  static const float ATTACK_DURATION;

  sf::Clock hitClock_;
  sf::Clock attackClock_;

  sf::Sprite character_;
  sf::Vector2f velocity_;

  State state_;
  Direction direction_;

  struct {
    sf::Texture * idle;
    sf::Texture * move;
    sf::Texture * jump;
    sf::Texture * attack;
    sf::Texture * hit;
  } sprites_;
};

#endif