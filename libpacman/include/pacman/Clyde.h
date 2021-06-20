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
protected:
  void determineTargetTile() override;

public:
  Clyde(Game* game);
};
}
#endif//PACMAN_CLYDE_H
