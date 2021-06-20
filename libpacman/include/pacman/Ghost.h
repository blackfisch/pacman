//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Moveable.h"
namespace Pacman
{
class Game;
class Ghost : public Moveable
{
protected:
  bool hasFear;
  sf::Vector2i homeTile;
  sf::Vector2i targetTile;
  virtual void determineTargetTile() = 0; //pure virtual
  void logicGhost();
  const std::vector<sf::Vector2i> housePosition = {
    sf::Vector2(10,12), sf::Vector2(11,12), sf::Vector2(12,12), sf::Vector2(13,12), sf::Vector2(14,12), sf::Vector2(15,12), sf::Vector2(16,12), sf::Vector2(17,12),
    sf::Vector2(10,13), sf::Vector2(11,13), sf::Vector2(12,13), sf::Vector2(13,13), sf::Vector2(14,13), sf::Vector2(15,13), sf::Vector2(16,13), sf::Vector2(17,13),
    sf::Vector2(10,14), sf::Vector2(11,14), sf::Vector2(12,14), sf::Vector2(13,14), sf::Vector2(14,14), sf::Vector2(15,14), sf::Vector2(16,14), sf::Vector2(17,14)
  };
  const sf::Vector2i houseExit = sf::Vector2i(13,10);

  template<typename Base, typename T>
  inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
  }

public:
  Ghost(Game* game, sf::Vector2i home);
  void logicFear();
//  bool wallReached();
  std::vector<sf::Vector2i> getFreeTiles();
  void update(float deltaTime);
  virtual ~Ghost() = default;
};
}

#endif//PACMAN_GHOST_H
