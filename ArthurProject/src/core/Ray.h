#pragma once
#include "core/Shape.h"
#include "SFML/System.hpp"
struct RaycastHit
{

};
class Ray
{
public:
	RaycastHit Cast(Ray A, const PolygonShape* B, const sf::Vector2f* bx_ptr);
};

