#pragma once
#include "SpriteRenderer.h"
#include "data/Animation.h"
#include <map>
#include <vector>
class Animator : public SpriteRenderer
{
public:
	Animator() : SpriteRenderer({ 0, 0 }, "Animator", sf::Texture()) {};
	Animator(const sf::Vector2f& aPosition, const std::string& aName, std::map<std::string, Animation*> someAnimations, std::string aStartAnim);
	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;
	void SetFrame(int aFrame);
	void SetAnimation(std::string aString);
private:
	void NextFrame();
	std::map<std::string, Animation*> myAnimations;
	std::string myCurrentAnimation;
	int myCurrentFrame;
	float myCurrentFrameTimer;
};

