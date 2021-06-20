#include <spdlog/spdlog.h>
#include "pacman/Pinky.h"
#include "pacman/Game.h"

namespace Pacman
{
Pinky::Pinky(Game *game): Ghost(game, sf::Vector2i(2, -2))
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/pinky.png"))
    spdlog::error("Error Loading texture file");
  else
    spdlog::debug("spritesheet for pinky loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(16 * 16, 14.5 * 16);
}

void Pinky::determineTargetTile()
{
  int distance = 0;
  int dir = gameObject->getPlayerDirectionIndex();
  sf::Vector2i pCurrent = gameObject->getPlayerTile();
  sf::Vector2i target = pCurrent;

  while (World::isInWorld(target) && distance < 4) {
    sf::Vector2i tempTarget = target;

    switch (dir) {
    case 0:
      tempTarget.y--;
      break;
    case 1:
      tempTarget.x++;
      break;
    case 2:
      tempTarget.y++;
      break;
    case 3:
      tempTarget.x--;
      break;
    }
    if (!World::isInWorld(tempTarget)) {
      dir = ++dir % 4;
      continue;
    }

    distance++;
    target = tempTarget;
  }

  targetTile = target;
}

}
