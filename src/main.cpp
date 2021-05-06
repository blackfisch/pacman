#include <iostream>
#include <string>

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

constexpr int window_width{ 288*3 }, window_height{ 224*3 };

using namespace std;

int main()
{
//  const std::string welt = "Welt";
//  const auto nachricht = fmt::format("Hallo {}!", welt);
//  std::cout << nachricht << std::endl;
//  std::cout << nachricht << '\n';
//  spdlog::info(nachricht);

  // Creation of the game window.
  sf::RenderWindow window{ sf::VideoMode{ window_width, window_height }, "Pac-Man" };
  window.setFramerateLimit(60);

  sf::Image icon;
  if (!icon.loadFromFile("res/pacman-art/pacman-right/2.png")) {
    cout << "ERROR" << endl;
  };
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Game loop
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