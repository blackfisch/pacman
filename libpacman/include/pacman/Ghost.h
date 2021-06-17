//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Moveable.h"
namespace Pacman
{
class Game;
class Ghost : public Moveable
{
protected:
  bool hasFear;
  sf::Vector2f homeCorner;
  sf::Vector2i targetTile;
  int getDirectionIndex();
  int getOppositeDirection(int dir);

public:
  Ghost(Game* game, sf::Vector2f home);
  void logicFear();
  bool wallReached();
  std::map<int,sf::Vector2i> getFreeSurroundingTiles();
  virtual void logicGhost() {};
  void update(float deltaTime);
  virtual ~Ghost() = default;
};
}

#endif//PACMAN_GHOST_H
