#include <iostream>
#include <string>

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

#include <pacman/Game.h>

constexpr int window_width{ 288*3 }, window_height{ 224*3 };

using namespace std;

int main()
{
//  const std::string welt = "Welt";
//  const auto nachricht = fmt::format("Hallo {}!", welt);
//  std::cout << nachricht << std::endl;
//  std::cout << nachricht << '\n';
//  spdlog::info(nachricht);


  Pacman::Game game = Pacman::Game(window_width, window_height);
  game.run();
}