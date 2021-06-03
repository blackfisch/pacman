#include "pacman/Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include "pacman/Pacman.h"
namespace Pacman
{

Game::Game(float scale) : scaleFactor(scale), player(Pacman(this)), world(World(this))
{
  spdlog::debug("Game created");
  spdlog::debug(scaleFactor);
  window_width = round(window_width * scaleFactor);
  window_height = round(window_height * scaleFactor);

  player.updateScale();
  world.updateScale();
}

void Game::handleInput(sf::RenderWindow &w, sf::Event &e)
{
  switch (e.key.code)
  {
    case sf::Keyboard::Escape:
      w.close();
      break;

    case sf::Keyboard::Up:
    case sf::Keyboard::W:
      player.setVelocity(sf::Vector2f(0, -1.7 * scaleFactor));
      player.setRotation(270);
      player.flipRight(scaleFactor);
      break;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      player.setVelocity(sf::Vector2f(-1.7 * scaleFactor, 0));
      player.setRotation(0);
      player.flipLeft(scaleFactor);
      break;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      player.setVelocity(sf::Vector2f(0, 1.7 * scaleFactor));
      player.setRotation(270);
      player.flipLeft(scaleFactor);
      break;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      player.setVelocity(sf::Vector2f(1.7 * scaleFactor, 0));
      player.setRotation(0);
      player.flipRight(scaleFactor);
      break;
  }
}

void Game::run()
{
  // Creation of the game window.
  sf::RenderWindow window{sf::VideoMode{ window_width, window_height }, "Pac-Man"};
  window.setFramerateLimit(60);

  sf::Image icon;
  if (!icon.loadFromFile("res/pacman-art/pacman/icon.png")) {
    spdlog::error("Error Loading icon file");
  };
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  sf::Clock clock;

  while (window.isOpen()) {
    float deltaTime = clock.getElapsedTime().asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        handleInput(window, event);
      }
    }

    window.clear(sf::Color::Black);

//    Update all game objects
    player.update(deltaTime);

//    Collision checks
    checkCollisionPlayerWorld();

//    Draw all game objects
    world.draw(window);
    player.draw(window);

    window.display();

//    Reset the clock
    clock.restart();
  }
}

float Game::getScale() const
{
  return scaleFactor;
}
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

  spdlog::debug(move);

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

    sf::Vector2f newPos = player.getShape().getPosition();

    // collision left
    if (move == "left" && playerBounds.left < (borderBounds.left + borderBounds.width - 2)) {
      player.setVelocity(sf::Vector2f(0, 0));

      newPos.x = border.getPosition().x + borderBounds.width + (borderBounds.width / 2);
      player.setPosition(newPos);

      spdlog::debug("1; collission at {}",i);
      return;
    }

    // collision right
    if (move == "right" && (playerBounds.left + playerBounds.width) > (borderBounds.left + 2)) {
      player.setVelocity(sf::Vector2f(0, 0));

      newPos.x = border.getPosition().x - (borderBounds.width / 2);
      player.setPosition(newPos);

      spdlog::debug("2; collission at {}",i);
      return;
    }

    //collision top
    if (move == "up" && playerBounds.top < (borderBounds.top + borderBounds.height - 2)) {
      player.setVelocity(sf::Vector2f(0, 0));

      newPos.y = border.getPosition().y + borderBounds.height + (borderBounds.height / 2);
      player.setPosition(newPos);

      spdlog::debug("3; collission at {}",i);
      return;
    }

    // collision bottom
    if (move == "down" && (playerBounds.top + playerBounds.height) > (borderBounds.top + 2)) {
      player.setVelocity(sf::Vector2f(0,0));

      newPos.y = border.getPosition().y - (borderBounds.height / 2);
      player.setPosition(newPos);

      spdlog::debug("4; collission at {}",i);
      return;
    }
  }
}
}
