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
private:
  void update(float deltaTime);

public:
  Inky(Game* game);
  void logicGhost();
};

}

#endif//PACMAN_INKY_H
