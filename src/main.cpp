#include <pacman/Game.h>
#include <spdlog/spdlog.h>
#include <string_view>

constexpr int window_width{ 288*3 }, window_height{ 224*3 };

int main(int argc, char* argv[])
{
  using namespace std::literals;

  if (argc > 1 && argv[1] == "--debug"sv)
    spdlog::set_level(spdlog::level::debug);

  Pacman::Game game = Pacman::Game(window_width, window_height);
  game.run();
}