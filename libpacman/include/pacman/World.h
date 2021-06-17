//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <pacman/Point.h>

namespace Pacman
{
enum class MapTiles {
  Point, // 25
  SuperPoint, // 50
  Fruit, // 75
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
  std::vector<Edible> edibles;
  Game *gameObject;
  float scale = 1.0f;
  std::vector<std::vector<MapTiles>> tileMap;

public:
  static const int boardSizeX = 28;
  static const int boardSizeY = 31;
  World(Game* game);
  void loadMap(const std::string&mapName);
  void displayMap();
  void draw(sf::RenderWindow &window);
  void updateScale();
  const std::vector<sf::Sprite> &getMapSprites() const;
  const std::vector<Edible> getEdibles() const;
  void setEdibles(const std::vector<Edible> &edibles);
  const std::vector<std::vector<MapTiles>> &getTileMap() const;
};
}


#endif//PACMAN_WORLD_H
