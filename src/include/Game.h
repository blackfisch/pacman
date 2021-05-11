//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Edible.h"

namespace Pacman
{
class Game
{
private:
  sf::RenderWindow window;
  World world;
  Pacman::Pacman player;
  Ghost[4] ghosts;
  std::vector<Edible> edibles;

public:
  void run();
};
}

#endif//PACMAN_GAME_H
