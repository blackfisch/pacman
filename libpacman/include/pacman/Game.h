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
//  Ghost ghosts[5];
  int pointCounter = 0;
  std::vector<Edible> edibles;
  unsigned int window_width = 576;
  unsigned int window_height = 496;
//  unsigned int window_height = 448;
  float scaleFactor = 1.0f;
  sf::View view;
  void scaleWindow(int windowWidth, int windowHeight);

public:
  static const int boardSizeX = 36;
  static const int boardSizeY = 28;
  Game(float scale);
  void run();
  void handleInput(sf::RenderWindow &window, sf::Event &e);
  float getScale() const;
  void checkCollisionPlayerWorld();
  void checkCollisionPlayerPoints();
};
}

#endif//PACMAN_GAME_H
