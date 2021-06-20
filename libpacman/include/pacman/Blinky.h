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
protected:
  void determineTargetTile() override;
public:
  Blinky(Game* game);
};
}

#endif//PACMAN_BLINKY_H
