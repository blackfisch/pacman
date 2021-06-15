#include <spdlog/spdlog.h>
#include "pacman/Clyde.h"

namespace Pacman
{
Clyde::Clyde(Game *game): Ghost(game)
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/clyde.png"))
    spdlog::error("Error Loading icon file");
  else
    spdlog::debug("spritesheet for clyde loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(312,216);
}

void Clyde::update(float deltaTime)
{
  Moveable::update(deltaTime);
}

void Clyde::logicGhost()
{
  return;
}

}
