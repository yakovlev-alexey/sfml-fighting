#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "state-manager.hpp"
#include "resource-holder.hpp"
#include "resource-declarations.hpp"

class Game : public sf::NonCopyable
{
public:
  Game();
  ~Game();

  void run();

  static Game & getInstance();

private:

  void processEvents();
  void update(const sf::Time & dt);
  void render();

  static Game * instance;

  const sf::Time FRAME_TIME = sf::seconds(1.0f / 60.0f);

  sf::RenderWindow window_;

  TextureHolder textures_;
  FontHolder fonts_;

  StateManager manager_;
};

#endif
