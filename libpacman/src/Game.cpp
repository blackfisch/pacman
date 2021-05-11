#include "pacman/Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

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
}

void Game::run()
{
  // Creation of the game window.
  sf::RenderWindow window{sf::VideoMode{ window_width, window_height }, "Pac-Man"};
  window.setFramerateLimit(60);

  sf::Image icon;
  if (!icon.loadFromFile("res/pacman-art/pacman-right/2.png")) {
    spdlog::error("Error Loading icon file");
  };
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
      }
    }

    window.clear(sf::Color::Black);
    window.display();
  }
}
}
