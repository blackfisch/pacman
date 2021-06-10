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
      Entity() = default;
      Entity(sf::Sprite sprite);
      virtual ~Entity() = default;
      virtual void update(float deltaTime);
      void draw(sf::RenderWindow &window);
      const sf::Sprite &getShape() const;
  };
}
#endif//PACMAN_ENTITY_H
