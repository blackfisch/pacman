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
  int getOppositeDirection(int dir);
  float speedModifier = 1;

public:
  Moveable(Game* game);
  Moveable(Game* game, float speedMod);
  const sf::Vector2f &getVelocity() const;
  void move(float deltaTime);
  void update(float deltaTime) override;
  void draw(sf::RenderWindow &window);
  void setVelocity(sf::Vector2f vel);
  sf::Vector2f getPosition();
  void updateScale();
  sf::Vector2i getCurrentTile();
  int getCurrentDirectionIndex();
  int getDirectionIndex(sf::Vector2f vel);
  void setPosition(sf::Vector2f pos);
  std::map<int,sf::Vector2i> getSurroundingTiles(sf::Vector2i);
  std::map<int,sf::Vector2i> getSurroundingTiles();
};
}


#endif//PACMAN_MOVEABLE_H
