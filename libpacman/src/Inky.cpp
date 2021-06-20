#include <spdlog/spdlog.h>
#include <pacman/World.h>
#include <pacman/Game.h>
#include "pacman/Inky.h"

namespace Pacman {
Inky::Inky(Game *game) : Ghost(game, sf::Vector2i(25, 32))
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/ghosts/inky.png"))
    spdlog::error("Error Loading texture file");
  else
    spdlog::debug("spritesheet for inky loaded successfully");

  texture.setSmooth(true);

  shape = sf::Sprite(texture);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(12 * 16, 14.5 * 16);
}

void Inky::determineTargetTile()
{
  int distance = 0;
  int dir = gameObject->getPlayerDirectionIndex();
  sf::Vector2i pCurrent = gameObject->getPlayerTile();
  sf::Vector2i target = pCurrent;

  while (World::isInWorld(target) && distance < 2) {
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

  sf::Vector2i toBlinkyAndBeyond = target + ((gameObject->getBlinkyTile() - target) * 2);
  if (!World::isInWorld(toBlinkyAndBeyond)) {
    int x = toBlinkyAndBeyond.x;
    int y = toBlinkyAndBeyond.x;
    int sizeX = World::boardSizeX;
    int sizeY = World::boardSizeY;

    toBlinkyAndBeyond.x = std::min(x, sizeX);
    toBlinkyAndBeyond.x = std::max(x, 0);

    toBlinkyAndBeyond.y = std::min(y, sizeY);
    toBlinkyAndBeyond.y = std::max(y, 0);
  }

  targetTile = toBlinkyAndBeyond;
}
}