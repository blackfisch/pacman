//
// Created by cpp on 11.05.21.
//

#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H
#include <SFML/Graphics.hpp>
#include <vector>
namespace Pacman{
class Entity
  {
    protected:
      sf::Sprite shape;
      sf::Texture texture;

    public:
      virtual void update();
      void draw(sf::RenderWindow &window);
      virtual ~Entity() = default;
  };
}
#endif//PACMAN_ENTITY_H
