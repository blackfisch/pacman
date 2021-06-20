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

void Game::handleGameInput(sf::RenderWindow &window, sf::Event &e)
{
  std::vector<sf::Sprite> walls = world.getMapSprites();
  sf::Rect<float> playerPos = player.getShape().getGlobalBounds();
  playerPos.height *= 0.8F;
  playerPos.width *= 0.8F;

  switch (e.key.code)
  {
    case sf::Keyboard::Escape:
      gameRunning = false;
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
void Game::handleMenuInput(sf::RenderWindow &window, sf::Event &e)
{
//    if (gameOver)
//      window.close();

    gameRunning = true;
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
  sf::Font pixelSans;
  pixelSans.loadFromFile("res/font/PixelSans.ttf");
  sf::Text fpsDisplay = sf::Text("FPS: --", pixelSans, 20);
  fpsDisplay.setPosition(10 * scaleFactor, 495 * scaleFactor);
  fpsDisplay.setFillColor(sf::Color(255,255,0));

  sf::Font megaPixel;
  megaPixel.loadFromFile("res/font/MegaPixel.ttf");
  sf::Text pointsDisplay = sf::Text("SCORE  0", megaPixel, 30);
  pointsDisplay.setPosition(window_width / 2 - 100, 495 * scaleFactor);
  pointsDisplay.setFillColor(sf::Color(255,255,255));

  sf::Text gameOverText = sf::Text("GAME OVER", megaPixel, 40);
  sf::FloatRect gameOverSize = gameOverText.getLocalBounds();
  gameOverText.setOrigin(sf::Vector2f(gameOverSize.left + gameOverSize.width / 2, gameOverSize.top + gameOverSize.height / 2));
  gameOverText.setPosition(window_width / 2, window_height / 2);
  gameOverText.setFillColor(sf::Color(255,255,0));
  gameOverText.setOutlineThickness(3);
  gameOverText.setOutlineColor(sf::Color(50,50,50));

  sf::Text highScore = sf::Text("HIGH SCORE: ", megaPixel, 35);
  sf::FloatRect highScoreSize = gameOverText.getLocalBounds();
  highScore.setOrigin(sf::Vector2f(highScoreSize.left + highScoreSize.width / 2, highScoreSize.top + highScoreSize.height / 2));
  highScore.setPosition(window_width / 2, window_height / 2 + 45 * scaleFactor);
  highScore.setFillColor(sf::Color(255,255,255));
  highScore.setOutlineThickness(2);
  highScore.setOutlineColor(sf::Color(50,50,50));

  sf::RectangleShape menuShade = sf::RectangleShape(sf::Vector2f(window_width,window_height));
  menuShade.setFillColor(sf::Color(10,10,10,200));
  menuShade.setPosition(0,0);
  sf::Text menuText = sf::Text("Press any Key to continue", pixelSans, 25);
  menuText.setFillColor(sf::Color(255,255,255));
  sf::FloatRect menuSize = menuText.getLocalBounds();
  menuText.setOrigin(sf::Vector2f(menuSize.left + menuSize.width / 2, menuSize.top + menuSize.height / 2));
  menuText.setPosition(window_width / 2, window_height / 2);

  int count = 0;
  float avgFps = 0;
  float fps = 0;

  // set initial velocity for ghosts
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
        if (gameRunning && !gameOver)
          handleGameInput(window, event);
        else
          handleMenuInput(window, event);
        break;

      case sf::Event::Resized:
        scaleWindow(event.size.width, event.size.height);
        break;
      }
    }

    window.clear(sf::Color::Black);
    window.setView(view);

//    Draw all game objects
    world.draw(window);
    player.draw(window);
    clyde.draw(window);
    blinky.draw(window);
    inky.draw(window);
    pinky.draw(window);

    if (gameOver) {
//        GAME OVER SCREEN
      highScore.setString("HIGH SCORE: " + std::to_string(pointCounter));
      highScoreSize = gameOverText.getLocalBounds();
      highScore.setOrigin(sf::Vector2f(highScoreSize.left + highScoreSize.width / 2, highScoreSize.top + highScoreSize.height / 2));

      window.draw(menuShade);
      window.draw(gameOverText);
      window.draw(highScore);
    } else {
      if (gameRunning) {
        //    GAME LOGIC

        //    Update all game objects
        player.update(deltaTime);

        blinky.update(deltaTime);
        clyde.update(deltaTime);
        inky.update(deltaTime);
        pinky.update(deltaTime);

        //    Collision checks
        checkCollisionPlayerWorld();
        checkCollisionPlayerPoints();
        checkCollisionPlayerGhosts();

        window.draw(fpsDisplay);
        window.draw(pointsDisplay);
      } else {
        //        MAIN MENU/PAUSE SCREEN
        window.draw(menuShade);
        window.draw(menuText);
      }
    }

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

  int moveDir = player.getCurrentDirectionIndex();

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
//    sf::Vector2f newPos = player.getPosition();
    newPos.x += 8 * scaleFactor;
    newPos.y += 8 * scaleFactor;

    //collision top
    if (moveDir == 0 && playerBounds.top < (borderBounds.top + borderBounds.height - 2)) {
      player.setVelocity(sf::Vector2f(0, 0));
      player.setPosition(newPos);

      spdlog::debug("3; collission at {}",i);
      return;
    }

    // collision right
    if (moveDir == 1 && (playerBounds.left + playerBounds.width) > (borderBounds.left + 2)) {
      player.setVelocity(sf::Vector2f(0, 0));
      player.setPosition(newPos);

      spdlog::debug("2; collission at {}",i);
      return;
    }

    // collision bottom
    if (moveDir == 2 && (playerBounds.top + playerBounds.height) > (borderBounds.top + 2)) {
      player.setVelocity(sf::Vector2f(0,0));
      player.setPosition(newPos);

      spdlog::debug("4; collission at {}",i);
      return;
    }

    // collision left
    if (moveDir == 3 && playerBounds.left < (borderBounds.left + borderBounds.width - 2)) {
      player.setVelocity(sf::Vector2f(0, 0));
      player.setPosition(newPos);

      spdlog::debug("1; collission at {}",i);
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
    gameOver = true;
    spdlog::error("GAME  OVER         GAME  OVER         GAME  OVER         GAME  OVER         GAME  OVER         ");
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

int Game::getPlayerDirectionIndex()
{
  return player.getCurrentDirectionIndex();
}

sf::Vector2i Game::getBlinkyTile()
{
  return blinky.getCurrentTile();
}
}
