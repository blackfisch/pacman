#include <spdlog/spdlog.h>
#include "pacman/Blinky.h"

namespace Pacman
{
Blinky::Blinky(Game *game): Ghost(game)
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/blinky.png"))
    spdlog::error("Error Loading icon file");
  else
    spdlog::debug("spritesheet for blinky loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(288,184);
}

void Blinky::update(float deltaTime)
{
  Moveable::update(deltaTime);
}

void Blinky::logicGhost()
{
  return;
}

}
