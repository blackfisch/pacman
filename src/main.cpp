#include <pacman/Game.h>

constexpr int window_width{ 288*3 }, window_height{ 224*3 };

int main()
{
  Pacman::Game game = Pacman::Game(window_width, window_height);
  game.run();
}