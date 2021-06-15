//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_CLYDE_H
#define PACMAN_CLYDE_H
#include "Ghost.h"
namespace Pacman
{
class Clyde : public Ghost
{
private:
  void update(float deltaTime);

public:
  Clyde(Game* game);
  void logicGhost();

};
}
#endif//PACMAN_CLYDE_H
