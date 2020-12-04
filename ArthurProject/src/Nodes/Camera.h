#pragma once
#include "Node.h"
#include "SFML/Graphics/View.hpp"
class Camera :
    public Node
{
public:
	Camera(const sf::Vector2f& aPosition,std::string aName);
	~Camera();

	void OnStart() override;
	void OnUpdate() override;
	inline void OnRender(sf::RenderWindow* aWindow) override { Node::OnRender(aWindow); };
	void SetPosition(const sf::Vector2f& aPosition);
	void Zoom(float aValue);
	float GetZoom();
	sf::Vector2f ScreenToWorldPoint(sf::Vector2f aPosition);
	sf::Vector2f ScreenToWorldPoint(sf::Vector2i aPosition);
	sf::Vector2i WorldToScreenPoint(sf::Vector2f aPosition);

private:
	 sf::View myView;
	 float myZoom;

};

