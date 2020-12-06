#pragma once
#include "PolygonCollider.h"
class BoxCollider :
	public PolygonCollider
{
public:
	BoxCollider(const sf::Vector2f& aPosition, const std::string& aName, int aWidth, int aHeight, const ColliderMaterial& aColMat = ColliderMaterial::Wood());
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetWidth(int aVal);
	void SetHeight(int aVal);	
	int GetWidth();
	int GetHeight();
private:
	int myWidth;
	int myHeight;
};

