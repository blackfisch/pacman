//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Moveable.h"
namespace Pacman
{
class Ghost : public Moveable
{
protected:
  bool hasFear;
public:
  void logicFear();
  virtual void logicGhost();
};
}

#endif//PACMAN_GHOST_H
