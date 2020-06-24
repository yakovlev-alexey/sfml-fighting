#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
  class Font;
  class Texture;
  class RenderTarget;
  class RenderStates;
}

namespace GUI
{

  class Button : public sf::Drawable, public sf::Transformable
  {
  public:
    Button();
    Button(sf::Font & font, const std::string & message);
    void setTextures(sf::Texture & btnTexture, sf::Texture & activeTexture);
    void setMessage(const std::string & message);
    void setFont(sf::Font & font);
    void setText(sf::Font & font, const std::string & message);
    void select();
    void deselect();
    void activate();
  protected:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
  private:
    void updateBackground();
    void updateMessage();
    sf::Sprite btn_;
    sf::Text message_;
    bool selected_;
    std::function<void()> callback_;
    sf::Texture * btnTexture_;
    sf::Texture * activeTexture_;
  }; 

}

#endif
