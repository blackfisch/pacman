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
    std::vector<float> position;
    sf::Sprite shape;
    sf::Texture texture;

    public:
    void update();
    void draw(sf::RenderWindow &window);
  };
}
#endif//PACMAN_ENTITY_H
