#include "Animator.h"
#include "Managers/AssetManager.h"
#include "TimeTracker.h"


Animator::Animator(const sf::Vector2f& aPosition, const std::string& aName, std::map<std::string, Animation*> someAnimations, std::string aStartAnim) : SpriteRenderer(aPosition, aName, AssetManager::GetTexture(someAnimations[aStartAnim]->TexturePath)), myAnimations(someAnimations), myCurrentAnimation(aStartAnim)
{
	myCurrentAnimation = aStartAnim;
	SetFrame(0);

}

void Animator::OnUpdate()
{
	SpriteRenderer::OnUpdate();
	if (myPlayingFlag)
	{
		if (myCurrentFrameTimer <= 0)
		{
			NextFrame();
		}
		else
		{
			myCurrentFrameTimer -= TimeTracker::GetDeltaTime();
		}
	}
}

void Animator::OnRender(sf::RenderWindow* aWindow)
{
	SpriteRenderer::OnRender(aWindow);


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
		if (myLoopFlag)
		{
			myCurrentFrame = 0;
		}
		else
		{
			myCurrentFrame--;
			myPlayingFlag = false;
			return;
		}
	}

	SetFrame(myCurrentFrame);
}

void Animator::SetAnimation(std::string aString)
{
	myCurrentAnimation = aString;
	mySprite->setTexture(AssetManager::GetTexture(myAnimations[aString]->TexturePath));
	SetFrame(0);
	myPlayingFlag = true;
}

void Animator::SetLoopFlag(bool aFlag)
{
	myLoopFlag = aFlag;
}

void Animator::SetPlayingFlag(bool aFlag)
{
	myPlayingFlag = aFlag;
}

bool Animator::GetPlayingFlag()
{
	return myPlayingFlag;
}

std::string Animator::GetCurrentAnimation()
{
	return myCurrentAnimation;
}
