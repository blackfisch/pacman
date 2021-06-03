
#include <pacman/World.h>
#include <pacman/Game.h>
#include <string>
#include <spdlog/spdlog.h>

namespace Pacman
{

World::World(Game* game): gameObject(game)
{
  if (!spriteSheet.loadFromFile("res/map/MapSprites.png"))
    spdlog::error("Error loading map sprites");

  spdlog::debug("map tiles loaded");

  MapTiles tileNames[12] = {
    MapTiles::CornerWallLeftTop, MapTiles::CornerWallRightBottom, MapTiles::CornerWallLeftBottom, MapTiles::CornerWallRightTop,
    MapTiles::WallHorizontal, MapTiles::WallVertical,
    MapTiles::JunctionWallRight, MapTiles::JunctionWallLeft, MapTiles::JunctionWallUp, MapTiles::JunctionWallDown,
    MapTiles::WallSingle,
    MapTiles::None
  };

  for (int i=0; i<12; ++i) {
//    sf::Sprite sprite = sf::Sprite(spriteSheet, sf::IntRect(16*i, 0, 16, 16));
    sf::IntRect rect = sf::IntRect(16*i, 0, 16, 16);
    spriteRects[tileNames[i]] = rect;
  }

  // TODO: Map Selection
  loadMap("Map1");

  displayMap();
}

void World::loadMap(std::string mapname)
{
  if (!mapMask.loadFromFile("res/map/" + mapname +".png"))
    spdlog::error("Error loading map mask");

  spdlog::debug("map mask loaded");
}

void World::displayMap()
{
  int width = Game::boardSizeX;
  int height = Game::boardSizeY;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      MapTiles spriteName = MapTiles::None;
      spdlog::debug("x: {} y: {}", x,  y);
      spdlog::debug("pixel: {}", (int)mapMask.getPixel(x,y).b);

      switch ((int)mapMask.getPixel(x,y).b) {
      case 100:
        spriteName = MapTiles::WallHorizontal;// 100
        break;
      case 110:
        spriteName = MapTiles::WallVertical;// 110
        break;
      case 120:
        spriteName = MapTiles::WallSingle;// 120
        break;
      case 130:
        spriteName = MapTiles::CornerWallLeftTop;// 130
        break;
      case 140:
        spriteName = MapTiles::CornerWallRightTop;// 140
        break;
      case 150:
        spriteName = MapTiles::CornerWallLeftBottom;// 150
        break;
      case 160:
        spriteName = MapTiles::CornerWallRightBottom;// 160
        break;
      case 170:
        spriteName = MapTiles::JunctionWallUp;// 170
        break;
      case 180:
        spriteName = MapTiles::JunctionWallDown;// 180
        break;
      case 190:
        spriteName = MapTiles::JunctionWallLeft;// 190
        break;
      case 200:
        spriteName = MapTiles::JunctionWallRight;// 200
      };

      if (spriteName == MapTiles::None)
        continue;

      sf::Sprite sprite = sf::Sprite(spriteSheet, spriteRects[spriteName]);

      spdlog::debug("x: {}, y: {}", x * 16 * scale, y * 16 * scale);
      spdlog::debug("x: {}, y: {}, scale: {}", x, y, scale);

      sprite.setPosition(x * 16, y * 16);

      mapSprites.push_back(sprite);
    }
  }
}

void World::draw(sf::RenderWindow &window)
{
  for (auto it = std::begin(mapSprites); it != std::end(mapSprites); ++it) {
//    spdlog::debug(*it);

//    spdlog::debug(sizeof(*it));
    window.draw(*it);
  }
}
void World::updateScale()
{
  float oldScale = scale;
  scale = gameObject->getScale();

  for (auto it = std::begin(mapSprites); it != std::end(mapSprites); ++it) {
    (*it).setScale((*it).getScale() / oldScale * scale);
    (*it).setPosition((*it).getPosition() / oldScale * scale);
  }
}
const std::vector<sf::Sprite> &World::getMapSprites() const
{
  return mapSprites;
}

}