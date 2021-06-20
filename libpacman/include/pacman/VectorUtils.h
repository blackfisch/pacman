//
// Created by cpp on 18.06.21.
//

#ifndef PACMAN_VECTORUTILS_H
#define PACMAN_VECTORUTILS_H

#include <SFML/Graphics.hpp>


namespace Pacman {
class VectorUtils
{
public:
  template<typename T>
  static float vectorMagnitude(sf::Vector2<T> vector)
  {
    return sqrt(pow(vector.x,2) + pow(vector.y,2));
  }

  template<typename T1, typename T2, typename T3>
  static sf::Vector2<T1> vectorBetween(sf::Vector2<T2> vectorA, sf::Vector2<T3> vectorB)
  {
    return (sf::Vector2<T1>)vectorA - (sf::Vector2<T1>)vectorB;
  }

  template<typename T1, typename T2>
  static float distanceBetween(sf::Vector2<T1> vectorA, sf::Vector2<T2> vectorB)
  {
    return vectorMagnitude(vectorBetween<float>(vectorA, vectorB));
  }

  template<typename T>
  static bool find(std::vector<sf::Vector2<T>> list, sf::Vector2<T> vector)
  {
    return (std::find(list.begin(), list.end(), vector) != list.end());
  }
};
}

#endif//PACMAN_VECTORUTILS_H
