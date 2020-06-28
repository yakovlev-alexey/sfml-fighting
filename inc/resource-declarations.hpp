#ifndef RESOURCE_DECLARATIONS_HPP
#define RESOURCE_DECLARATIONS_HPP

namespace sf
{
  class Texture;
  class Font;
}

namespace Textures
{
  enum ID
  {
    Background,
    Button,
    ActiveButton,
    PlayerIdle,
    PlayerMove,
    PlayerJump,
    PlayerAttack,
    PlayerHit,
    OpponentIdle,
    OpponentMove,
    OpponentJump,
    OpponentAttack,
    OpponentHit
  };
}

namespace Fonts
{
  enum ID
  {
    Primary
  };
}

template <typename I, typename R>
class ResourceHolder;

typedef ResourceHolder<Textures::ID, sf::Texture> TextureHolder;
typedef ResourceHolder<Fonts::ID, sf::Font>       FontHolder;

#endif
