#include "pacman/Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include "pacman/Pacman.h"
namespace Pacman
{

Game::Game(float scale) : scaleFactor(scale), player(Pacman(this))
{
  spdlog::debug("Game created");
  spdlog::debug(scaleFactor);
  window_width = round(window_width * scaleFactor);
  window_height = round(window_height * scaleFactor);

  player.updateScale();
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
      player.setVelocity(sf::Vector2f(0, -2 * scaleFactor));
      player.setRotation(270);
      player.flipRight(scaleFactor);
      break;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      player.setVelocity(sf::Vector2f(-2 * scaleFactor, 0));
      player.setRotation(0);
      player.flipLeft(scaleFactor);
      break;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      player.setVelocity(sf::Vector2f(0, 2 * scaleFactor));
      player.setRotation(270);
      player.flipLeft(scaleFactor);
      break;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      player.setVelocity(sf::Vector2f(2 * scaleFactor, 0));
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

//    Draw all game objects
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
}
