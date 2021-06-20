//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_POINT_H
#define PACMAN_POINT_H

#include "Edible.h"
#include <SFML/Graphics.hpp>

namespace Pacman
{
class Point : public Edible
{
public:
  Point(sf::Sprite sprite);
};
}

#endif//PACMAN_POINT_H
