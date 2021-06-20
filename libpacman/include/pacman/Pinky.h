//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_PINKY_H
#define PACMAN_PINKY_H
#include "Ghost.h"
namespace Pacman
{
class Pinky : public Ghost
{
protected:
  void determineTargetTile() override;

public:
  Pinky(Game* game);
};
}


#endif//PACMAN_PINKY_H
