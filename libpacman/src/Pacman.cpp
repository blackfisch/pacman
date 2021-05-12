#include "pacman/Pacman.h"
#include "pacman/Moveable.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

namespace Pacman
{
  Pacman::Pacman()
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/pacman-right/1.png")) {
    spdlog::error("Error Loading icon file");
  }
  shape.setTexture(texture);
}
}
