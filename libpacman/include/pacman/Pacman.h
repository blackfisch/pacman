//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include <vector>

namespace Pacman
{
class Game;
class Pacman : public Moveable
{
private:
  sf::IntRect spriteSource;
  sf::Clock clock;
  Game *gameObject;

public:
  Pacman(Game* game);
  void setRotation(float angle);
  void animate();
  void update(float deltaTime);
  void flipLeft(float scale);
  void flipRight(float scale);
  void updateScale();
  void setPosition(sf::Vector2f pos);
};
}
#endif//PACMAN_PACMAN_H
