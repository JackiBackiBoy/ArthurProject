#include "Animator.h"
#include "Managers/AssetManager.h"
#include "TimeTracker.h"


Animator::Animator(const sf::Vector2f& aPosition, const std::string& aName, std::map<std::string, Animation*> someAnimations, std::string aStartAnim) : SpriteRenderer(aPosition, aName, AssetManager::GetTexture(someAnimations[aStartAnim]->TexturePath)), myAnimations(someAnimations), myCurrentAnimation(aStartAnim)
{
	myCurrentAnimation = aStartAnim;
	SetFrame(0);
	CenterOrigin();

}

void Animator::OnUpdate()
{
	SpriteRenderer::OnUpdate();
}

void Animator::OnRender(sf::RenderWindow* aWindow)
{
	SpriteRenderer::OnRender(aWindow);

	if (myCurrentFrameTimer <= 0)
	{
		NextFrame();
	}
	else
	{
		myCurrentFrameTimer -= TimeTracker::GetDeltaTime();
	}
}

void Animator::SetFrame(int aFrame)
{
	AnimationFrame* tempFrame = &myAnimations[myCurrentAnimation]->Frames[aFrame];

	mySprite->setTextureRect(sf::IntRect(tempFrame->Origin, tempFrame->Size));

	myCurrentFrameTimer = tempFrame->Time;
	myCurrentFrame = aFrame;

}

void Animator::NextFrame()
{
	myCurrentFrame++;

	if (myCurrentFrame >= myAnimations[myCurrentAnimation]->FrameCount)
	{
		myCurrentFrame = 0;
	}

	SetFrame(myCurrentFrame);
}

void Animator::SetAnimation(std::string aString)
{
	myCurrentAnimation = aString;
	mySprite->setTexture(AssetManager::GetTexture(myAnimations[aString]->TexturePath));
	CenterOrigin();
}

void Animator::CenterOrigin()
{
	mySprite->setOrigin((sf::Vector2f)(myAnimations[myCurrentAnimation]->Frames[0].Size) / 2.f);
}
