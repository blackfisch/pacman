#include "pacman/Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include "pacman/Pacman.h"
namespace Pacman
{

Game::Game(unsigned int width, unsigned int height)
{
  window_width = width;
  window_height = height;
  Game();
}

Game::Game() {
  spdlog::debug("Game created");
  player = Pacman();
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
      player.setVelocity(sf::Vector2f(0, -2));
      player.setRotation(270);
      player.flipRight();
      break;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      player.setVelocity(sf::Vector2f(-2, 0));
      player.setRotation(0);
      player.flipLeft();
      break;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      player.setVelocity(sf::Vector2f(0, 2));
      player.setRotation(270);
      player.flipLeft();
      break;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      player.setVelocity(sf::Vector2f(2, 0));
      player.setRotation(0);
      player.flipRight();
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


  while (window.isOpen()) {
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
    player.update();

//    Draw all game objects
    player.draw(window);

    window.display();
  }
}
}
