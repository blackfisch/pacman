#include <spdlog/spdlog.h>
#include "pacman/Blinky.h"
#include "pacman/Game.h"
#include "pacman/VectorUtils.h"
#include <random>

namespace Pacman
{
Blinky::Blinky(Game *game): Ghost(game,sf::Vector2i(25, -2))
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/blinky.png"))
    spdlog::error("Error Loading texture file");
  else
    spdlog::debug("spritesheet for blinky loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(14 * 16, 11.5 * 16);
}

void Blinky::determineTargetTile()
{
  targetTile = gameObject->getPlayerTile();
}

}
