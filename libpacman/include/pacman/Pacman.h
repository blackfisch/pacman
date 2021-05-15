//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Moveable.h"
#include <vector>

namespace Pacman
{
class Pacman : public Moveable
{
private:
  sf::IntRect spriteSource;
  sf::Clock clock;

public:
  Pacman();
  void setRotation(float angle);
  void animate();
  void update();
  void flipLeft();
  void flipRight();
};
}
#endif//PACMAN_PACMAN_H
