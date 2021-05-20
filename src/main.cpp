#include <pacman/Game.h>
#include <spdlog/spdlog.h>
#include <string_view>

int main(int argc, char* argv[])
{
  using namespace std::literals;

  if (argc > 1 && argv[1] == "--debug"sv)
    spdlog::set_level(spdlog::level::debug);

  Pacman::Game game{ 1 };
  game.run();
}