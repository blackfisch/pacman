#include "pacman/Pacman.h"
#include "pacman/Moveable.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include <iostream>

namespace Pacman
{
Pacman::Pacman()
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/pacman/pacman_spritesheet.png"))
    spdlog::error("Error Loading icon file");

  shape.setTexture(texture);
  spriteSource = sf::IntRect(-16,0,16,16);
  shape = sf::Sprite(texture,spriteSource);

  sf::Rect size = shape.getLocalBounds();
  shape.setOrigin(size.width / 2, size.height / 2);
  shape.setPosition(100,100);
}

void Pacman::setRotation(float angle)
{
  shape.setRotation(angle);
}

void Pacman::animate()
{
  if (clock.getElapsedTime().asSeconds() > .1f) {
    spriteSource.left += 16;
    shape.setTextureRect(spriteSource);

    if (spriteSource.left >= 32)
      spriteSource.left = -16;

    clock.restart();
  }
}

void Pacman::update()
{
  Moveable::update();
  animate();
}

void Pacman::flipLeft()
{
  shape.setScale(-1,1);
}

void Pacman::flipRight()
{
  shape.setScale(1,1);
}
}
