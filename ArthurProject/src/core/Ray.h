#pragma once
#include "SFML/System.hpp"
#include <Graphics.hpp>
struct RaycastHit
{
	sf::Vector2f IntersectPoint;
};
class Ray
{
public:
	static bool Cast();
	static void DrawRay(const sf::Vector2f& anOrigin, const sf::Vector2f& anEndpoint, const sf::Color&, sf::RenderWindow* aWindow);
};

