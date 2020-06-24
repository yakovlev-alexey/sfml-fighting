#include "button.hpp"

#include <iostream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

GUI::Button::Button() :
  Transformable{ },
  btn_{ },
  message_{ },
  selected_{ false },
  btnTexture_{ nullptr },
  activeTexture_{ nullptr }
{ }

GUI::Button::Button( sf::Font & font, const std::string & message) :
  Transformable{ },
  btn_{ },
  message_{ message, font },
  selected_{ false },
  btnTexture_{ nullptr },
  activeTexture_{ nullptr }
{
  updateBackground();
  updateMessage();  
}

void GUI::Button::setTextures(sf::Texture & btnTexture, sf::Texture & activeTexture)
{
  btnTexture_ = &btnTexture;
  activeTexture_ = &activeTexture;
  btn_.setTexture(selected_ ? activeTexture : btnTexture);
  updateBackground();
}

void GUI::Button::setMessage(const std::string & message)
{
  message_.setString(message);
  updateMessage();
}

void GUI::Button::setFont(sf::Font & font)
{
  message_.setFont(font);
  updateMessage();
}

void GUI::Button::setText(sf::Font & font, const std::string & message)
{
  message_.setFont(font);
  message_.setString(message);
  updateMessage();
}

void GUI::Button::select()
{
  selected_ = true;
  if (activeTexture_) {
    btn_.setTexture(*activeTexture_);
  }
}
void GUI::Button::deselect()
{
  selected_ = false;
  if (btnTexture_) {
    btn_.setTexture(*btnTexture_);
  }
}

void GUI::Button::activate()
{
  callback_();
}

void GUI::Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(btn_, states);
  target.draw(message_, states);
}

void GUI::Button::updateBackground()
{
  sf::FloatRect bb = btn_.getLocalBounds();
  btn_.setOrigin(bb.left + bb.width / 2.0f, bb.top + bb.height / 2.0f);
  btn_.setPosition(0.0f, 0.0f);
}

void GUI::Button::updateMessage()
{
  message_.setFillColor(sf::Color::White);
  message_.setOutlineColor(sf::Color::Black);
  message_.setOutlineThickness(0.5f);
  sf::FloatRect bb = message_.getLocalBounds();
  message_.setOrigin(bb.left + bb.width / 2.0f, bb.top + bb.height / 2.0f);
  message_.setPosition(0.0f, 0.0f);
}
