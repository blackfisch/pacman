#include "pacman/Entity.h"
#include <SFML/Graphics.hpp>

namespace Pacman {

void Entity::update()
{
  return;
}

void Entity::draw(sf::RenderWindow &window)
{
  window.draw(shape);
}

}
