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

public:
  Ghost(Game* game);
  void logicFear();
  virtual void logicGhost() {};
  virtual ~Ghost() = default;
};
}

#endif//PACMAN_GHOST_H
