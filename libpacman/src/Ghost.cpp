#include <spdlog/spdlog.h>
#include <pacman/VectorUtils.h>
#include "pacman/Ghost.h"
#include "pacman/Game.h"
#include "pacman/World.h"
#include <algorithm>

namespace Pacman
{
Ghost::Ghost(Game* game, sf::Vector2i home): homeTile(home), Moveable(game, 0.6) {

}

void Ghost::logicFear()
{
  return;
}

void Ghost::logicGhost()
{
  determineTargetTile();

  if (VectorUtils::find(housePosition, getCurrentTile())) {
    targetTile = houseExit;
    spdlog::debug("set target to exit");
  }

  sf::Vector2f currentTile = (sf::Vector2f)getCurrentTile();

  std::vector<sf::Vector2i> freeTiles = getFreeTiles();
  float minDist = INFINITY;
  sf::Vector2i nextTile;

  for (sf::Vector2i& tile : freeTiles) {
    float distance = VectorUtils::distanceBetween(targetTile, tile);
    if (distance < minDist) {
      minDist = distance;
      nextTile = tile;
    }
  }

  nextTile.x -= currentTile.x;
  nextTile.y -= currentTile.y;

  setVelocity((sf::Vector2f)nextTile);
}

//bool Ghost::wallReached()
//{
//  if (velocity == sf::Vector2f())
//    return true;
//
//  sf::Vector2i currentTile = getCurrentTile();
//  int direction = getCurrentDirectionIndex();
//
//  //check if is already centered, otherwise let it move
//  sf::FloatRect position = getShape().getGlobalBounds();
//  position.left += position.width / 2;
//  position.top += position.height / 2;
//  sf::Vector2f center = (sf::Vector2f)currentTile * (16 * gameObject->getScale());
//  center.x += 8 * gameObject->getScale();
//  center.y += 8 * gameObject->getScale();
//
//  if (abs(position.left - center.x) > 1 * gameObject->getScale() || abs(position.top - center.y) > 1 * gameObject->getScale())
//    return false;
//
//  return !(getFreeSurroundingTiles().contains(direction));
//}
std::vector<sf::Vector2i> Ghost::getFreeTiles()
{
  std::map<int, sf::Vector2i> surroundingTiles = getSurroundingTiles();
  int curDir = getCurrentDirectionIndex();
  int oppositeDir = getOppositeDirection(curDir);
  std::vector<sf::Vector2i> freeTiles;

  for (auto tile : surroundingTiles) {
    if (tile.second != sf::Vector2i() && tile.first != oppositeDir)
      if (!VectorUtils::find(housePosition, tile.second) || VectorUtils::find(housePosition, getCurrentTile()))
        freeTiles.push_back(tile.second);
  }

  return freeTiles;
}
void Ghost::update(float deltaTime)
{
  Moveable::update(deltaTime);

  logicGhost();
}

}
