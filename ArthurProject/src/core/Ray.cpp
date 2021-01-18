#include "Ray.h"
bool Ray::Cast()
{
	//// Calculates denominator of equations
	//for (int i = 0; i < collisions; i++) {
	//	sf::Vector2f tempPos3 = collisions[i]->Position;
	//	sf::Vector2f tempPos4 = collisions[i]->Position + collisions[i]->SurfaceVector;
	//	const float den = (tempPos1.x - tempPos2.x) * (tempPos3.y - tempPos4.y) - (tempPos1.y - tempPos2.y) * (tempPos3.x - tempPos4.x);

	//	if (den == 0)
	//		continue;

	//	const float t = ((tempPos1.x - tempPos3.x) * (tempPos3.y - tempPos4.y) - (tempPos1.y - tempPos3.y) * (tempPos3.x - tempPos4.x)) / den;
	//	const float u = -((tempPos1.x - tempPos2.x) * (tempPos1.y - tempPos3.y) - (tempPos1.y - tempPos2.y) * (tempPos1.x - tempPos3.x)) / den;

	//	// If there's an intersection...
	//	if (t > 0 && t < 1 && u > 0 && u < 1)
	//	{
	//		// Gets intersection point
	//		sf::Vector2f tempIntersectPoint = sf::Vector2f(tempPos1.x + t * (tempPos2.x - tempPos1.x), tempPos1.y + t * (tempPos2.y - tempPos1.y));
	//		RaycastHit.IntersectPoint = tempIntersectPoint;
	//	}
	//}

	return true;
}


void Ray::DrawRay(const sf::Vector2f& anOrigin, const sf::Vector2f& anEndpoint, const sf::Color& aColor, sf::RenderWindow* aWindow)
{
	sf::VertexArray tempArr = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
	tempArr[0].position = anOrigin;
	tempArr[1].position = anEndpoint;
	tempArr[0].color = aColor;
	tempArr[1].color = aColor;
	aWindow->draw(tempArr);
}



//void ray::calc_hit(Vector2f p3, Vector2f p4)
//{
//	const Vector2f p1 = g_mouse_pos;
//	const Vector2f p2 = m_end;
//
//	// Calculates denominator of equations
//	const float den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
//
//	if (den == 0)
//		return;
//
//	const float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / den;
//	const float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / den;
//
//	// If there's an intersection...
//	if (t > 0 && t < 1 && u > 0 && u < 1)
//	{
//		// Gets intersection point
//		m_end.x = p1.x + t * (p2.x - p1.x);
//		m_end.y = p1.y + t * (p2.y - p1.y);
//	}
//}
