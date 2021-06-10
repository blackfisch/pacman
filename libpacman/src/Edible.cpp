#include "pacman/Edible.h"

namespace Pacman {
Edible::Edible(sf::Sprite sprite, int value): pointValue(value), Entity(sprite)
{}

int Edible::getPointValue() const
{
  return pointValue;
}
}