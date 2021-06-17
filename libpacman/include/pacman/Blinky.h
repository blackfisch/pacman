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
public:
  Blinky(Game* game);
  void logicGhost() override;
  void update(float deltaTime);
};
}

#endif//PACMAN_BLINKY_H
