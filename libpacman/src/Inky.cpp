#include <spdlog/spdlog.h>
#include "pacman/Inky.h"

namespace Pacman
{
Inky::Inky(Game *game): Ghost(game, sf::Vector2f(25, 32))
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/inky.png"))
    spdlog::error("Error Loading icon file");
  else
    spdlog::debug("spritesheet for inky loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(12 * 16,14.5 * 16);
}

void Inky::update(float deltaTime)
{
  Moveable::update(deltaTime);
}

void Inky::logicGhost()
{
  return;
}

}
