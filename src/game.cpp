#include "game.hpp"

#include <memory>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "state.hpp"
#include "menu-state.hpp"
#include "resource-holder.hpp"
#include "resource-declarations.hpp"

namespace 
{
  const unsigned int WINDOW_WIDTH = 800u;
  const unsigned int WINDOW_HEIGHT = 600u;
}

Game::Game() :
  window_{ sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Game window", sf::Style::Close },
  textures_{ },
  fonts_{ },
  state_{ std::make_unique<MenuState>(window_, textures_, fonts_) }
{ 
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

void Game::processEvents()
{
  sf::Event event;
  while (window_.pollEvent(event)) {

    switch (event.type) {

      case sf::Event::Closed:
        window_.close();
      default:
        break;
    }
  }
}

void Game::update(const sf::Time &)
{
  state_->update();
}

void Game::render()
{
  state_->render();
}
