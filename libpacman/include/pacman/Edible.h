//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_EDIBLE_H
#define PACMAN_EDIBLE_H
#include "Entity.h"
#include <SFML/Graphics.hpp>

namespace Pacman {
class Edible : public Entity
{
protected:
  int pointValue;

public:
  Edible(sf::Sprite sprite, int value = 1);
  int getPointValue() const;
//  void eat();
};
}

#endif//PACMAN_EDIBLE_H
