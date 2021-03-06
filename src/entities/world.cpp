#include <entities/world.hpp>

#include <string>
#include <iostream>
#include <stdexcept>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <resource-holder.hpp>
#include <entities/character.hpp>
#include <states/state-manager.hpp>
#include <resource-declarations.hpp>
#include <states/state-declarations.hpp>

const float World::FLOOR_HEIGHT = 50.0f;

const float World::HBAR_HEIGHT = 20.0f;

World::World(const State::context_t & context) :
  screenSize_{ context.window.getSize() },
  player_{ context.textures },
  opponent_{ context.textures, player_ },
  bg_{ },
  hbarWidth_{ screenSize_.x / 2.0f - 100.0f },
  playerHbar_{ },
  opponentHbar_{ },
  playerTxt_{ },
  opponentTxt_{ },
  timer_{ },
  clock_{ }
{
  try {
    bg_.setTexture(context.textures.getOrLoad(Textures::Background, "data/textures/forest-background.png"));
    bg_.setScale(0.5f, 0.5f);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  player_.setPosition(screenSize_.x - 150.0f, screenSize_.y - 150.0f);
  opponent_.setPosition(150.0f, screenSize_.y - 150.0f);


  updateHbars();

  float hbarPadding = 25.0f;
  playerHbar_.setPosition(screenSize_.x - hbarPadding, hbarPadding);
  opponentHbar_.setPosition(hbarPadding, hbarPadding);

  try {
    sf::Font & primary = context.fonts.getOrLoad(Fonts::Primary, "data/fonts/primary.ttf");
    playerTxt_.setFont(primary);
    opponentTxt_.setFont(primary);

    playerTxt_.setString("PLAYER");
    opponentTxt_.setString("OPPONENT");

    playerTxt_.setCharacterSize(static_cast<int>(HBAR_HEIGHT) - 2);
    opponentTxt_.setCharacterSize(static_cast<int>(HBAR_HEIGHT) - 2);

    playerTxt_.setPosition(screenSize_.x - hbarPadding, hbarPadding);
    playerTxt_.setOrigin(playerTxt_.getLocalBounds().width, 0);
    opponentTxt_.setPosition(hbarPadding, hbarPadding);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sf::Font & accent = context.fonts.getOrLoad(Fonts::Primary, "data/fonts/primary.ttf");

    timer_.setFont(accent);
    timer_.setCharacterSize(HBAR_HEIGHT);
    timer_.setPosition(screenSize_.x / 2.0f, hbarPadding);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }  
}

void World::handleEvent(const sf::Event & event)
{
  player_.handleEvent(event);
  opponent_.handleEvent(event);
}

void World::update(const sf::Time & dt)
{
  handlePhysics(player_);

  handlePhysics(opponent_);

  player_.update(dt);

  opponent_.update(dt);

  player_.moveVelocity();
  handleCollisions(player_);

  opponent_.moveVelocity();
  handleCollisions(opponent_);

  handleInteraction(player_, opponent_);

  // TODO: gameover screen
  if (opponent_.isDead()) {
    StateManager::getInstance().queueChange(States::Menu);
  } else if (player_.isDead()) {
    StateManager::getInstance().queueChange(States::Menu);
  }

  updateHbars();  

  updateTimer();
}

void World::render(sf::RenderWindow & window) const
{
  // TODO: interface and pause menu
  window.draw(bg_);

  window.draw(opponentHbar_);
  window.draw(playerHbar_);

  window.draw(opponentTxt_);
  window.draw(playerTxt_);

  window.draw(timer_);

  window.draw(opponent_);
  window.draw(player_);
}

void World::handlePhysics(Character & character) const
{
  sf::FloatRect bb = character.getBounds();

  float groundedError = 5.0f;

  character.setGrounded((bb.top + bb.height) > (screenSize_.y - FLOOR_HEIGHT - groundedError));
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

void World::handleInteraction(Character & char1, Character & char2) const
{
  Character::State s1 = char1.getState();
  Character::State s2 = char2.getState();

  if ((s1 != Character::State::Attack && s2 != Character::State::Attack)
      || s1 == Character::State::Dead || s2 == Character::State::Dead) {
    return;
  }

  sf::FloatRect bb1 = char1.getBounds();
  sf::FloatRect bb2 = char2.getBounds();

  if (s1 == Character::State::Attack && s2 != Character::State::Hit && bb1.intersects(bb2)) {
    char2.damage(char1.getDamage(), ((bb2.left - bb1.left) > 0.0f) ? Character::Direction::Right : Character::Direction::Left);
  } else if (s2 == Character::State::Attack && s1 != Character::State::Hit && bb2.intersects(bb1)) {
    char1.damage(char2.getDamage(), ((bb1.left - bb2.left) > 0.0f) ? Character::Direction::Right : Character::Direction::Left);
  }
}

static sf::Color getHealthBarColor(float h);

void World::updateHbars()
{
  float maxHealth = Character::getMaxHealth();


  float playerHealth = player_.getHealth() / maxHealth;

  playerHbar_.setSize(sf::Vector2f(-(playerHealth * hbarWidth_), HBAR_HEIGHT));  
  playerHbar_.setFillColor(getHealthBarColor(playerHealth));


  float opponentHealth = opponent_.getHealth() / maxHealth;

  opponentHbar_.setSize(sf::Vector2f(opponentHealth * hbarWidth_, HBAR_HEIGHT));  
  opponentHbar_.setFillColor(getHealthBarColor(opponentHealth));
}

void World::updateTimer()
{
  float tss = clock_.getElapsedTime().asSeconds();
  
  if (player_.getHealth() == 0.0f) {
    timer_.setString("OPPONENT WINS!");
  } else if (opponent_.getHealth() == 0.0f) {
    timer_.setString("PLAYER WINS!");
  } else if (tss > 1.0f) {
    timer_.setString(std::to_string(static_cast<int>(tss)));
  } else {
    timer_.setString("FIGHT!");
  }

  sf::FloatRect bb = timer_.getLocalBounds();
  timer_.setOrigin(bb.left + bb.width / 2.0f, bb.top + bb.height / 2.0f);
}

static sf::Color getHealthBarColor(float h)
{
  return (h > 0.5f) 
      ? sf::Color::Green
      : (h > 0.25f)
        ? sf::Color::Yellow
        : sf::Color::Red;
}
