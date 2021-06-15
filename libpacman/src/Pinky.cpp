#include <spdlog/spdlog.h>
#include "pacman/Pinky.h"

namespace Pacman
{
Pinky::Pinky(Game *game): Ghost(game)
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/pinky.png"))
    spdlog::error("Error Loading icon file");
  else
    spdlog::debug("spritesheet for pinky loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(288,216);
}

void Pinky::update(float deltaTime)
{
  Moveable::update(deltaTime);
}

void Pinky::logicGhost()
{
  return;
}

}
