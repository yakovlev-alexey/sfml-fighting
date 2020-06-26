#include <states/menu.hpp>

#include <memory>
#include <iostream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <states/game-state.hpp>
#include <states/state-manager.hpp>
#include <states/state-declarations.hpp>

#include <gui/button.hpp>
#include <gui/container.hpp>

#include <resource-holder.hpp>
#include <resource-declarations.hpp>

Menu::Menu(TextureHolder & textures, FontHolder & fonts) :
  logo_{ },
  btnContainer_{ },
  bg_{ }
{
  try {
    bg_.setTexture(textures.getOrLoad(Textures::Background, "data/textures/forest-background.png"));
    bg_.setScale(0.5f, 0.5f);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  auto playBtn = std::make_unique<GUI::Button>();
  playBtn->setCallback([]() {
    StateManager::getInstance().queueChange(States::Game);
  });

  auto exitBtn = std::make_unique<GUI::Button>();
  exitBtn->setCallback([]() {
    StateManager::getInstance().queueChange(States::Exit);
  });

  logo_.setPosition(400, 50);
  playBtn->setPosition(400, 125);
  exitBtn->setPosition(400, 200);
  
  try {
    sf::Font & font = fonts.getOrLoad(Fonts::Primary, "data/fonts/primary.ttf");
    playBtn->setText(font, "Play");
    exitBtn->setText(font, "Exit");
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  try {
    sf::Texture btnTexture = textures.getOrLoad(Textures::Button, "data/textures/btn.png");
    sf::Texture activeTexture = textures.getOrLoad(Textures::ActiveButton, "data/textures/btn-active.png");
    playBtn->setTextures(btnTexture, activeTexture);
    exitBtn->setTextures(btnTexture, activeTexture);
  } catch (std::runtime_error & exc) {
    std::cerr << exc.what() << '\n';
  }

  btnContainer_.add(playBtn);
  btnContainer_.add(exitBtn);

}

void Menu::handleEvent(const sf::Event & event)
{
  btnContainer_.handleEvent(event);
}

void Menu::render(sf::RenderWindow & window) const
{
  window.draw(bg_);
  window.draw(logo_);
  btnContainer_.render(window);
}
