#include "pacman/Pacman.h"
#include "pacman/Moveable.h"
#include "pacman/Game.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include <iostream>

namespace Pacman
{
Pacman::Pacman(Game* game): gameObject(game)
{
  texture = sf::Texture();
  if (!texture.loadFromFile("res/pacman-art/pacman/pacman_spritesheet.png"))
    spdlog::error("Error Loading icon file");
  else
    spdlog::debug("spritesheet for player loaded successfully");

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

void Pacman::update(float deltaTime)
{
  Moveable::update(deltaTime);
  animate();
}

void Pacman::flipLeft(float scale)
{
  shape.setScale(-1 * scale,1 * scale);
}

void Pacman::flipRight(float scale)
{
  shape.setScale(1 * scale,1 * scale);
}
void Pacman::updateScale()
{
  shape.setScale(gameObject->getScale(), gameObject->getScale());
}
}
