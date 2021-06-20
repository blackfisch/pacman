//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_INKY_H
#define PACMAN_INKY_H
#include "Ghost.h"
namespace Pacman
{
class Inky : public Ghost
{
protected:
  void determineTargetTile() override;

public:
  Inky(Game* game);
};

}

#endif//PACMAN_INKY_H
