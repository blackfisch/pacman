#include <spdlog/spdlog.h>
#include "pacman/Clyde.h"
#include "pacman/Game.h"
#include "pacman/VectorUtils.h"

namespace Pacman
{
Clyde::Clyde(Game *game): Ghost(game, sf::Vector2i(2, 33))
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/clyde.png"))
    spdlog::error("Error Loading texture file");
  else
    spdlog::debug("spritesheet for clyde loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(14 * 16, 14.5 * 16);
}

void Clyde::determineTargetTile()
{
  sf::Vector2i playerTile = gameObject->getPlayerTile();
  sf::Vector2i currentTile = getCurrentTile();

  if (VectorUtils::distanceBetween(playerTile, currentTile) > 8)
    targetTile = playerTile;
  else
    targetTile = homeTile;
}

}
