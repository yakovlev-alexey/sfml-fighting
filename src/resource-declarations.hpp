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
    Background
  };
}

namespace Fonts
{
  enum ID
  {
    Main
  };
}

template <typename I, typename R>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>       FontHolder;

#endif
