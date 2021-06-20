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
#include "Clyde.h"
#include "Blinky.h"
#include "Inky.h"
#include "Pinky.h"

namespace Pacman
{

class Game
{
private:
  World world;
  Pacman player;
  Clyde clyde;
  Blinky blinky;
  Inky inky;
  Pinky pinky;
  int pointCounter = 0;
  std::vector<Edible> edibles;
  unsigned int window_width;
  unsigned int window_height;
  float scaleFactor = 1.0f;
  sf::View view;
  bool gameRunning = false;
  bool gameOver = false;
  void scaleWindow(int windowWidth, int windowHeight);

public:
  Game(float scale);
  void run();
  void handleGameInput(sf::RenderWindow &window, sf::Event &e);
  void handleMenuInput(sf::RenderWindow &window, sf::Event &e);
  float getScale() const;
  void checkCollisionPlayerWorld();
  void checkCollisionPlayerPoints();
  void checkCollisionPlayerGhosts();
  const World &getWorld() const;
  sf::Vector2i getPlayerTile();
  int getPlayerDirectionIndex();
  sf::Vector2i getBlinkyTile();
};
}

#endif//PACMAN_GAME_H
