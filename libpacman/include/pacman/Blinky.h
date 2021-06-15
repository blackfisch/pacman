//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_BLINKY_H
#define PACMAN_BLINKY_H

#include "Ghost.h"
namespace Pacman
{
class Blinky : public Ghost
{
private:
  void update(float deltaTime);

public:
  Blinky(Game* game);
  void logicGhost();
};
}

#endif//PACMAN_BLINKY_H
