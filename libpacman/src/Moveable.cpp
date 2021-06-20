#include "pacman/Moveable.h"
#include "pacman/Game.h"
#include <spdlog/spdlog.h>

namespace Pacman{
Moveable::Moveable(Game* game): gameObject(game) {

}

Moveable::Moveable(Game *game, float speedMod): speedModifier(speedMod), gameObject(game)
{
}

void Moveable::update(float deltaTime)
{
  move(deltaTime);
}

void Moveable::move(float deltaTime)
{
  int curDir = getCurrentDirectionIndex();
  sf::Vector2f vel = velocity * (1.0f + deltaTime) * speedModifier;
  sf::Vector2i tile = getCurrentTile();
  sf::Vector2f newPos = getPosition();
  sf::Vector2f tilePos = (sf::Vector2f)tile * (16 * gameObject->getScale());

  if (curDir % 2 == 0) {
        newPos.x += tilePos.x + 8 * gameObject->getScale();
        vel.x = 0;
  } else {
        newPos.y += tilePos.y + 8 * gameObject->getScale();
        vel.y = 0;
    }

//    shape.setPosition(newPos);
    shape.move(vel);
}
void Moveable::setVelocity(sf::Vector2f vel)
{
  int curDir = getCurrentDirectionIndex();
  int newDir = getDirectionIndex(vel);
  float scale = gameObject->getScale();

//  diretion change 90 degrees
  if ((curDir + newDir) % 2 != 0) {
    sf::Vector2i tile = getCurrentTile();
    sf::Vector2f newPos = (sf::Vector2f)tile * (16 * scale);
//    sf::Vector2f newPos = player.getPosition();
    newPos.x += 8 * scale;
    newPos.y += 8 * scale;
    setPosition(newPos);
  }

  velocity = vel;
}
void Moveable::draw(sf::RenderWindow &window)
{
  sf::Vector2 shapePos = shape.getPosition();
  int shapeW = shape.getLocalBounds().width;
  int shapeH = shape.getLocalBounds().height;

  if (shapePos.x - shapeW/2 > window.getSize().x) {
    spdlog::debug("right edge");
    shape.setPosition(-shapeW/2, shapePos.y);
  } else if (shapePos.x + shapeW/2 < 0) {
    spdlog::debug("left edge");
    shape.setPosition(window.getSize().x + shapeW/2, shapePos.y);
  } else if (shapePos.y - shapeH/2 > window.getSize().y) {
    spdlog::debug("bottom edge");
    shape.setPosition(shapePos.x, -shapeH/2);
  } else if (shapePos.y + shapeH/2 < 0) {
    spdlog::debug("top edge");
    shape.setPosition(shapePos.x,window.getSize().y + shapeH/2);
  }

  Entity::draw(window);
}

const sf::Vector2f &Moveable::getVelocity() const
{
  return velocity;
}
void Moveable::updateScale()
{
  shape.setScale(gameObject->getScale(), gameObject->getScale());
}
sf::Vector2i Moveable::getCurrentTile()
{
  sf::Vector2i position;
  sf::FloatRect bounds = this->getShape().getGlobalBounds();

  position.x = div((bounds.left + bounds.width / 2), 16 * gameObject->getScale()).quot;
  position.y = div((bounds.top + bounds.height / 2), 16 * gameObject->getScale()).quot;

  return position;
}

int Moveable::getDirectionIndex(sf::Vector2f vel)
{
  if (vel.y < 0) {
    // moving up
    return 0;
  } else if (vel.x > 0) {
    // moving right
    return 1;
  } else if (vel.y > 0) {
    // moving down
    return 2;
  } else if (vel.x < 0) {
    // moving left
    return 3;
  } else {
    // not moving probably
    return -1;
  }
}

int Moveable::getCurrentDirectionIndex()
{
  return getDirectionIndex(velocity);
}

int Moveable::getOppositeDirection(int dir)
{
  if (dir == -1)
    return -1;

  return (dir + 2) % 4;
}

sf::Vector2f Moveable::getPosition()
{
  sf::FloatRect bounds = shape.getGlobalBounds();

  return sf::Vector2f(bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2));
}

void Moveable::setPosition(sf::Vector2f pos)
{
  shape.setPosition(pos);
}

std::map<int,sf::Vector2i> Moveable::getSurroundingTiles(sf::Vector2i currentTile)
{
  std::vector<std::vector<MapTiles>> walls = gameObject->getWorld().getTileMap();
  std::map<int,sf::Vector2i> surroundingTiles;
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

    if (!World::isInWorld(nextTile)) {
      continue;
    }

    MapTiles tileType = walls[nextTile.y][nextTile.x];

    if (tileType == MapTiles::Point || tileType == MapTiles::PowerPellet || tileType == MapTiles::Fruit || tileType == MapTiles::None) {
      surroundingTiles[it - offsets.begin()] = nextTile;
    }
  }

  return surroundingTiles;
}

std::map<int,sf::Vector2i> Moveable::getSurroundingTiles()
{
  return getSurroundingTiles(getCurrentTile());
}
}