//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_MOVEABLE_H
#define PACMAN_MOVEABLE_H
#include <vector>
#include "Entity.h"
namespace Pacman{
class Game;
class Moveable : public Entity
{
protected:
  sf::Vector2f velocity;
  Game *gameObject;

public:
  Moveable(Game* game);
  const sf::Vector2f &getVelocity() const;
  void move(float deltaTime);
  void update(float deltaTime) override;
  void draw(sf::RenderWindow &window);
  void setVelocity(sf::Vector2f vel);
  void updateScale();
  sf::Vector2i getCurrentTile();
};
}


#endif//PACMAN_MOVEABLE_H
