#include <game.hpp>

#include <memory>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <states/state.hpp>
#include <states/menu-state.hpp>
#include <resource-holder.hpp>
#include <resource-declarations.hpp>

Game * Game::instance = nullptr;

namespace 
{
  const unsigned int WINDOW_WIDTH = 800u;
  const unsigned int WINDOW_HEIGHT = 600u;
}

Game::Game() :
  window_{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT }, "Game window", sf::Style::Close },
  textures_{ },
  fonts_{ },
  manager_{ { window_, textures_, fonts_ } }
{ 
  if (Game::instance != nullptr) {
    throw std::runtime_error{ "Game::Game() : Only a single instance of a Game can be initialized simultaneously" };
  }

  Game::instance = this;

  try {
    textures_.load(Textures::Background, "data/textures/forest-background.png");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    fonts_.load(Fonts::Primary, "data/fonts/primary.ttf");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

}

Game::~Game()
{
  Game::instance = nullptr;
}

void Game::run()
{
  sf::Clock clock;
  // Track time since last update to execute fixed updates every FRAME_TIME
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  // Main game loop
  while (window_.isOpen()) {

    sf::Time deltaTime = clock.restart();
    timeSinceLastUpdate += deltaTime;

    // Every frame start execute queued fixed updates (fixed time updates)
    while (timeSinceLastUpdate > FRAME_TIME) {

      timeSinceLastUpdate -= FRAME_TIME;

      processEvents();
      update(FRAME_TIME);
    }

    // After fixed updates are executed, render the next frame
    render();
  }
}

Game & Game::getInstance() 
{
  return *Game::instance;
}

void Game::processEvents()
{
  sf::Event event;
  while (window_.pollEvent(event)) {

    if (event.type == sf::Event::Closed) {
      window_.close();
      return;
    } else {
      manager_.processEvent(event);
    }
  }
}

void Game::update(const sf::Time & dt)
{
  manager_.update(dt);
}

void Game::render()
{
  manager_.render();
}
