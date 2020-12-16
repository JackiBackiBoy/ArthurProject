#pragma once
#include "SFML/System.hpp"
#include <Graphics.hpp>
struct RaycastHit
{
	sf::Vector2f IntersectPoint;
	float Dist;
	sf::Vector2f Normal;
};
class Ray
{
public:
	static bool Cast();
	static void DrawRay(const sf::Vector2f& anOrigin, const sf::Vector2f& aDirection, float aDistance, const sf::Color&, sf::RenderWindow* aWindow);
};

