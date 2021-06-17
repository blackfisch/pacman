#include <spdlog/spdlog.h>
#include "pacman/Ghost.h"
#include "pacman/Game.h"
#include "pacman/World.h"

namespace Pacman
{
Ghost::Ghost(Game* game, sf::Vector2f home): homeCorner(home), Moveable(game) {

}

void Ghost::logicFear()
{
  return;
}

bool Ghost::wallReached()
{
  if (velocity == sf::Vector2f())
    return true;

  sf::Vector2i currentTile = getCurrentTile();
  int direction = getDirectionIndex();

  //check if is already centered, otherwise let it move
  sf::FloatRect position = getShape().getGlobalBounds();
  position.left += position.width / 2;
  position.top += position.height / 2;
  sf::Vector2f center = (sf::Vector2f)currentTile * (16 * gameObject->getScale());
  center.x += 8 * gameObject->getScale();
  center.y += 8 * gameObject->getScale();

  if (abs(position.left - center.x) > 1 * gameObject->getScale() || abs(position.top - center.y) > 1 * gameObject->getScale())
    return false;

  return !(getFreeSurroundingTiles().contains(direction));
}
std::map<int,sf::Vector2i> Ghost::getFreeSurroundingTiles()
{
  std::vector<std::vector<MapTiles>> walls = gameObject->getWorld().getTileMap();
  std::map<int,sf::Vector2i> freeTiles;
  sf::Vector2i currentTile = getCurrentTile();
  sf::Vector2i nextTile;

  std::vector<sf::Vector2i> offsets = {
    sf::Vector2i(0, -1),
    sf::Vector2i(1, 0),
    sf::Vector2i(0, 1),
    sf::Vector2i(-1, 0)
  };

  for (auto it = offsets.begin(); it != offsets.end(); ++it){
      nextTile = currentTile;
      nextTile.x += it->x;
      nextTile.y += it->y;

      if (nextTile.x > World::boardSizeX || nextTile.x < 0 || nextTile.y > World::boardSizeY || nextTile.y < 0) {
        continue;
      }

      MapTiles tileType = walls[nextTile.y][nextTile.x];

      if (tileType == MapTiles::Point || tileType == MapTiles::SuperPoint || tileType == MapTiles::Fruit || tileType == MapTiles::None) {
        freeTiles[it - offsets.begin()] = nextTile;
      }
  }

  return freeTiles;
}
void Ghost::update(float deltaTime)
{
//  logicGhost();
  Moveable::update(deltaTime);
}
int Ghost::getDirectionIndex()
{
  if (velocity.y < 0) {
    // moving up
    return 0;
  } else if (velocity.x > 0) {
    // moving right
    return 1;
  } else if (velocity.y > 0) {
    // moving down
    return 2;
  } else if (velocity.x < 0) {
    // moving left
    return 3;
  } else {
    spdlog::error("something is wrong! v = ({},{})", velocity.x, velocity.y);
    return -1;
  }
}

int Ghost::getOppositeDirection(int dir)
{
  switch (dir) {
  case 0:
    return 2;
  case 1:
    return 3;
  case 2:
    return 0;
  case 3:
    return 1;
  default:
    return -1;
  }
}

}
