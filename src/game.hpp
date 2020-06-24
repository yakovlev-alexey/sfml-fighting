#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "state.hpp"
#include "resource-holder.hpp"
#include "resource-declarations.hpp"

class Game
{
public:
  Game();
  void run();
private:

  void processEvents();
  void update(const sf::Time & deltaTime);
  void render();

  const sf::Time FRAME_TIME = sf::seconds(1.0f / 60.0f);

  sf::RenderWindow window_;

  TextureHolder textures_;
  FontHolder fonts_;

  std::unique_ptr<State> state_;

};

#endif
