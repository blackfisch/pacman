//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H

#include "Edible.h"
namespace Pacman
{
class Fruit : public Edible
{
public:
  Fruit(sf::Sprite sprite);
};
}
#endif//PACMAN_FRUIT_H
