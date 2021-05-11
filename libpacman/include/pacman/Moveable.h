//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_MOVEABLE_H
#define PACMAN_MOVEABLE_H
#include <vector>
#include "Entity.h"
namespace Pacman{
class Moveable : public Entity
{
protected:

  std::vector<float> velocity;

public:

  void move();
};
}


#endif//PACMAN_MOVEABLE_H
