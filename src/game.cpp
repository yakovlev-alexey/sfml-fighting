#include "game.hpp"

Game::Game(unsigned int windowWidth, unsigned int windowHeight) :
  window_{ sf::VideoMode{windowWidth, windowHeight}, "Game window", sf::Style::Close },
  texHolder_{ },
  fontHolder_{ }
{ }

void Game::run()
{
  sf::Clock clock;
  // Track time since last update to execute fixed updates every FRAME_TIME
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  // Main game loop
  while (window_.isOpen()) {

    sf::Time deltaTime = clock.restart();
    timeSinceLastUpdate += deltaTime;

    // Every frame execute fixed updates (fixed time)
    while (timeSinceLastUpdate > FRAME_TIME) {

      timeSinceLastUpdate -= FRAME_TIME;

      processEvents();
      update(FRAME_TIME);
    }

    // After fixed updates executed, render next frame
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

}

void Game::render()
{

}
