#include "pacman/Moveable.h"
#include <spdlog/spdlog.h>

namespace Pacman{

void Moveable::update()
{
  move();
}

void Moveable::move()
{
  shape.move(velocity);
}
void Moveable::setVelocity(sf::Vector2f vel)
{
  velocity = vel;
}
void Moveable::draw(sf::RenderWindow &window)
{
  sf::Vector2 shapePos = shape.getPosition();
  int shapeW = shape.getLocalBounds().width;
  int shapeH = shape.getLocalBounds().height;

  if (shapePos.x - shapeW/2 > window.getSize().x) {
    spdlog::debug("right edge");
    shape.setPosition(-shapeW/2, shapePos.y);
  } else if (shapePos.x + shapeW/2 < 0) {
    spdlog::debug("left edge");
    shape.setPosition(window.getSize().x + shapeW/2, shapePos.y);
  } else if (shapePos.y - shapeH/2 > window.getSize().y) {
    spdlog::debug("bottom edge");
    shape.setPosition(shapePos.x, -shapeH/2);
  } else if (shapePos.y + shapeH/2 < 0) {
    spdlog::debug("top edge");
    shape.setPosition(shapePos.x,window.getSize().y + shapeH/2);
  }

  Entity::draw(window);
}

}