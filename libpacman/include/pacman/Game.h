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
  World world;
  Pacman player;
  Ghost ghosts[5];
  std::vector<Edible> edibles;
  unsigned int window_width = 288;
  unsigned int window_height = 224;


public:
  Game();
  Game(unsigned int width, unsigned int height);
  void run();
};
}

#endif//PACMAN_GAME_H
