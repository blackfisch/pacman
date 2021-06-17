#include <spdlog/spdlog.h>
#include "pacman/Blinky.h"
#include "pacman/Game.h"

namespace Pacman
{
Blinky::Blinky(Game *game): Ghost(game,sf::Vector2f(25, -2))
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
  shape.setPosition(14 * 16, 11.5 * 16);
}

void Blinky::update(float deltaTime)
{
  Ghost::update(deltaTime);
}

void Blinky::logicGhost()
{
  targetTile = gameObject->getPlayerTile();

//  only move on, if we reach a wall
  if (!wallReached()) {
    spdlog::debug("not reached");
    return;
  }

  int direction = getOppositeDirection(getDirectionIndex());
  std::map<int,sf::Vector2i> surroundingTiles = this->getFreeSurroundingTiles();
  std::vector<sf::Vector2i> freeTiles;
  for (auto tile : surroundingTiles) {
    if (tile.second != sf::Vector2i() && tile.first != direction)
      freeTiles.push_back(tile.second);
  }

  sf::Vector2f nextTile = (sf::Vector2f)freeTiles[rand() % freeTiles.size()];

  sf::Vector2f currentTile = (sf::Vector2f)getCurrentTile();
  nextTile.x -= currentTile.x;
  nextTile.y -= currentTile.y;

  setVelocity(nextTile);
  spdlog::debug("new vel: {} {}", nextTile.x, nextTile.y);
}

}
