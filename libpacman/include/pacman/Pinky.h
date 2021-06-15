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
private:
  void update(float deltaTime);

public:
  Pinky(Game* game);
  void logicGhost();

};
}


#endif//PACMAN_PINKY_H
