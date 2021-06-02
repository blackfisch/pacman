//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

namespace Pacman
{
enum class MapTiles {
  None, // 0
  WallHorizontal, // 100
  WallVertical, // 110
  WallSingle, // 120
  CornerWallLeftTop, // 130
  CornerWallRightTop, // 140
  CornerWallLeftBottom, // 150
  CornerWallRightBottom, // 160
  JunctionWallUp, // 170
  JunctionWallDown, // 180
  JunctionWallLeft, // 190
  JunctionWallRight // 200
};

class Game;
class World
{
private:
  sf::Texture spriteSheet;
  std::map<MapTiles, sf::IntRect> spriteRects;
  std::vector<sf::Sprite> mapSprites;
  sf::Image mapMask;
  std::vector<std::vector<float>> obstacles;
  Game *gameObject;
  float scale = 1.0f;

public:
  World(Game* game);
  void loadMap(std::string mapname);
  void displayMap();
  void draw(sf::RenderWindow &window);
  void updateScale();
};
}


#endif//PACMAN_WORLD_H
