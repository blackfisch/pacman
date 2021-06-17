#include "pacman/Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <pacman/Clyde.h>
#include "pacman/Pacman.h"
namespace Pacman
{

Game::Game(float scale) :
                          scaleFactor(scale),
                          player(Pacman(this)),
                          world(World(this)),
                          clyde(Clyde(this)),
                          blinky(Blinky(this)),
                          inky(Inky(this)),
                          pinky(Pinky(this)),
                          window_width(roundf(World::boardSizeX * 16 * scale)),
                          window_height(roundf(World::boardSizeY * 16 * scale + 50 * scale))
{
  spdlog::debug("Game created");
  spdlog::debug(scaleFactor);

  player.updateScale();
  world.updateScale();
}

void Game::handleInput(sf::RenderWindow &w, sf::Event &e)
{
  std::vector<sf::Sprite> walls = world.getMapSprites();
  sf::Rect<float> playerPos = player.getShape().getGlobalBounds();
  playerPos.height *= 0.8F;
  playerPos.width *= 0.8F;

  switch (e.key.code)
  {
    case sf::Keyboard::Escape:
      w.close();
      break;

    case sf::Keyboard::Up:
    case sf::Keyboard::W:
      // prevent rotating towards a wall
      playerPos.top -= 8 * scaleFactor;
      for (const auto wall : walls) {
        if (wall.getGlobalBounds().intersects(playerPos))
          return;
      }

      player.setVelocity(sf::Vector2f(0, -1 * scaleFactor));
      player.setRotation(270);
      player.flipRight(scaleFactor);
      break;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      // prevent rotating towards a wall
      playerPos.left -= 8 * scaleFactor;
      for (const auto wall : walls) {
        if (wall.getGlobalBounds().intersects(playerPos))
          return;
      }

      player.setVelocity(sf::Vector2f(-1 * scaleFactor, 0));
      player.setRotation(0);
      player.flipLeft(scaleFactor);
      break;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      // prevent rotating towards a wall
      playerPos.top += 8 * scaleFactor;
      for (const auto wall : walls) {
        if (wall.getGlobalBounds().intersects(playerPos))
          return;
      }

      player.setVelocity(sf::Vector2f(0, 1 * scaleFactor));
      player.setRotation(270);
      player.flipLeft(scaleFactor);
      break;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      // prevent rotating towards a wall
      playerPos.width += 8 * scaleFactor;
      for (const auto wall : walls) {
        if (wall.getGlobalBounds().intersects(playerPos))
          return;
      }

      player.setVelocity(sf::Vector2f(1 * scaleFactor, 0));
      player.setRotation(0);
      player.flipRight(scaleFactor);
      break;
  }
}

void Game::run()
{
  // Creation of the game window.
  sf::RenderWindow window{sf::VideoMode{ window_width, window_height }, "Pac-Man"};
  window.setFramerateLimit(120);

  view.setSize(window_width, window_height);
  view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
  scaleWindow(window_width, window_height);

  sf::Image icon;
  if (!icon.loadFromFile("res/pacman-art/pacman/icon.png")) {
    spdlog::error("Error Loading icon file");
  };
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  sf::Clock clock;
  sf::Font fpsFont;
  fpsFont.loadFromFile("res/font/PixelSans.ttf");
  sf::Text fpsDisplay = sf::Text("FPS: --", fpsFont, 20);
  fpsDisplay.setPosition(10 * scaleFactor, 495 * scaleFactor);
  fpsDisplay.setFillColor(sf::Color(255,255,0));

  sf::Font pointFont;
  pointFont.loadFromFile("res/font/MegaPixel.ttf");
  sf::Text pointsDisplay = sf::Text("SCORE  0", pointFont, 30);
  pointsDisplay.setPosition(window_width / 2 - 100, 495 * scaleFactor);
  pointsDisplay.setFillColor(sf::Color(255,255,255));


  int count = 0;
  float avgFps = 0;
  float fps = 0;

  //test#
  blinky.setVelocity(sf::Vector2f(1,0));

  while (window.isOpen()) {
    float deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();

    avgFps += 1.f / deltaTime;
    ++count;
    if (count == 5) {
      fps = avgFps / 5.0f;
      count = 0;
    }


    fpsDisplay.setString("FPS: " + std::to_string((int)std::min(std::round(fps), 120.0f)));
    pointsDisplay.setString("SCORE  " + std::to_string(pointCounter));

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        handleInput(window,event);
        break;

      case sf::Event::Resized:
        scaleWindow(event.size.width, event.size.height);
        break;
      }
    }

    window.clear(sf::Color::Black);

    window.setView(view);

//    Update all game objects
    player.update(deltaTime);
    blinky.update(deltaTime);

    if (blinky.wallReached()) {
      spdlog::debug("wall reached");
      blinky.setVelocity(sf::Vector2f(0,0));
      blinky.logicGhost();
    } else
      spdlog::debug("wall not reached");

//    Collision checks
    checkCollisionPlayerWorld();
    checkCollisionPlayerPoints();
    checkCollisionPlayerGhosts();

//    Draw all game objects
    world.draw(window);
    player.draw(window);
    clyde.draw(window);
    blinky.draw(window);
    inky.draw(window);
    pinky.draw(window);


    window.draw(fpsDisplay);
    window.draw(pointsDisplay);

    window.display();
  }
}

float Game::getScale() const
{
  return scaleFactor;
}
void Game::checkCollisionPlayerPoints()
{
  std::vector<Edible> food = world.getEdibles();

  for (auto it = std::begin(food); it != std::end(food); ++it) {
    if (player.getShape().getGlobalBounds().intersects(it->getShape().getGlobalBounds())) {
      food.erase(it);
      pointCounter += it->getPointValue();
      world.setEdibles(food);
      spdlog::debug("point!");
      return;
    }
  }
};
void Game::checkCollisionPlayerWorld()
{
  std::vector<sf::Sprite> mapBorders = world.getMapSprites();
  sf::Rect<float> playerBounds = player.getShape().getGlobalBounds();

  std::string move;
  if (player.getVelocity().x < 0) {
    move = "left";
  } else if (player.getVelocity().x > 0) {
    move = "right";
  } else if (player.getVelocity().y < 0) {
    move = "up";
  } else if (player.getVelocity().y > 0) {
    move = "down";
  } else {
    return;
  }

  spdlog::debug("Tile: {} {}",player.getCurrentTile().x, player.getCurrentTile().y);

//  spdlog::debug(move);

  int i = 0;
  for (sf::Sprite border : mapBorders) {
    ++i;
    sf::Rect<float> borderBounds = border.getGlobalBounds();

    if (
        playerBounds.left >= borderBounds.left + borderBounds.width ||
        playerBounds.left + playerBounds.width <= borderBounds.left ||
        playerBounds.top >= borderBounds.top + borderBounds.height ||
        playerBounds.top + playerBounds.height <= borderBounds.top
      ) {
      continue;
    }

    sf::Vector2i tile = player.getCurrentTile();
    sf::Vector2f newPos = (sf::Vector2f)tile * (16 * scaleFactor);
    newPos.x += 8 * scaleFactor;
    newPos.y += 8 * scaleFactor;

    // collision left
    if (move == "left" && playerBounds.left < (borderBounds.left + borderBounds.width - 2)) {
      player.setVelocity(sf::Vector2f(0, 0));
      player.setPosition(newPos);

      spdlog::debug("1; collission at {}",i);
      return;
    }

    // collision right
    if (move == "right" && (playerBounds.left + playerBounds.width) > (borderBounds.left + 2)) {
      player.setVelocity(sf::Vector2f(0, 0));
      player.setPosition(newPos);

      spdlog::debug("2; collission at {}",i);
      return;
    }

    //collision top
    if (move == "up" && playerBounds.top < (borderBounds.top + borderBounds.height - 2)) {
      player.setVelocity(sf::Vector2f(0, 0));
      player.setPosition(newPos);

      spdlog::debug("3; collission at {}",i);
      return;
    }

    // collision bottom
    if (move == "down" && (playerBounds.top + playerBounds.height) > (borderBounds.top + 2)) {
      player.setVelocity(sf::Vector2f(0,0));
      player.setPosition(newPos);

      spdlog::debug("4; collission at {}",i);
      return;
    }
  }
}


void Game::checkCollisionPlayerGhosts()
{
  sf::FloatRect playerBounds = player.getShape().getGlobalBounds();

  if (
    playerBounds.intersects(inky.getShape().getGlobalBounds()) ||
    playerBounds.intersects(pinky.getShape().getGlobalBounds()) ||
    playerBounds.intersects(blinky.getShape().getGlobalBounds()) ||
    playerBounds.intersects(clyde.getShape().getGlobalBounds())
    ) {
    spdlog::error("GAME OVER");
  }

}

///
/// Source: https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
///
void Game::scaleWindow(int windowWidth, int windowHeight)
{
  float windowRatio = windowWidth / (float) windowHeight;
  float viewRatio = view.getSize().x / (float) view.getSize().y;
  float sizeX = 1;
  float sizeY = 1;
  float posX = 0;
  float posY = 0;

  bool horizontalSpacing = true;
  if (windowRatio < viewRatio)
    horizontalSpacing = false;

  // If horizontalSpacing is true, the black bars will appear on the left and right side.
  // Otherwise, the black bars will appear on the top and bottom.

  if (horizontalSpacing) {
    sizeX = viewRatio / windowRatio;
    posX = (1 - sizeX) / 2.f;
  } else {
    sizeY = windowRatio / viewRatio;
    posY = (1 - sizeY) / 2.f;
  }

  view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
}
const World &Game::getWorld() const
{
  return world;
}

sf::Vector2i Game::getPlayerTile()
{
  return player.getCurrentTile();
}
}
