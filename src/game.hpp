#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "resource-holder.hpp"
#include "resource-declarations.hpp"

class Game
{
public:
  Game(unsigned int windowWidth = 800u, unsigned int windowHeight = 600u);
  void run();
private:

  void processEvents();
  void update(const sf::Time & deltaTime);
  void render();

  const sf::Time FRAME_TIME = sf::seconds(1.0f / 60.0f);

  sf::RenderWindow window_;

  TextureHolder texHolder_;
  FontHolder fontHolder_;

};

#endif
