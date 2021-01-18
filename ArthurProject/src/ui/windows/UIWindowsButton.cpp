#include "UIWindowsButton.h"

UIWindowsButton::UIWindowsButton(const std::string& aText, const sf::Vector2f& aPosition, const std::string& aName)
	: UIButton(aPosition, aName, new UIText(aPosition, aName, aText, sf::Color::Black, "Fonts/segoeui", 64), 41, 19, sf::Color::White, nullptr)
{
	myHoverColor = sf::Color(229, 243, 255);
	myBorderHoverColor = sf::Color(204, 232, 255);
	myBorderTexture = new sf::Texture();

	// Create border texture
	if (myBorderTexture->create(myWidth, myHeight))
	{
		tempPixels = new sf::Uint8[myWidth * myHeight * 4] { 0 };

		for (int i = 0; i < myWidth * myHeight * 4; i++)
		{
			int tempY = (i / 4) / myWidth;
			int tempX = (i / 4) - myWidth * tempY;

			// Only add pixels to the buffer if it is along the border
			if (tempX == 0 || tempX == myWidth - 1 || tempY == 0 || tempY == myHeight - 1)
			{
				tempPixels[i] = 255;
			}
		}

		myBorderTexture->update(tempPixels);

		myBorderSprite = sf::Sprite(*myBorderTexture);
		myBorderSprite.setPosition(GetPosition());
		myBorderSprite.setColor(myBorderHoverColor);
	}
	else
	{
		std::cout << "Error creating texture" << std::endl;
	}

	// Calculate correct y-scaling to apply, along with adjusted width
	float tempAdjustedScaleY = (float)(myHeight * 0.5f) / 50;
	myTextPointer->SetFontSize(tempAdjustedScaleY * myTextPointer->GetFontSize());

	SetWidth(myTextPointer->GetTextWidth() * 2);
}

void UIWindowsButton::OnUpdate()
{
	UIButton::OnUpdate();

	myBorderSprite.setPosition(GetPosition());
}

void UIWindowsButton::OnRender(sf::RenderWindow* aWindow)
{
	UIButton::OnRender(aWindow);

	if (myIsHovered)
	{
		sf::Color tempBorderColor = myBorderSprite.getColor();
		myBorderSprite.setColor({ tempBorderColor.r, tempBorderColor.g, tempBorderColor.b, (sf::Uint8)myAlpha });
		aWindow->draw(myBorderSprite);
	}
	else
	{

	}
}