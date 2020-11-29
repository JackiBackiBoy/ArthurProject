#include "UIWindowsButton.h"

UIWindowsButton::UIWindowsButton(const std::string& aText, const sf::Vector2f& aPosition, Node* aParent)
	: UIButton(aPosition, aParent, new UIText(aPosition, nullptr, aText, sf::Color::Black, "Fonts/segoeui", 64), 41, 19, sf::Color::White, nullptr)
{
	//myBorderShape = sf::RectangleShape({ myWidth, myHeight });
	//myBorderShape.

	myHoverColor = sf::Color(229, 243, 255);
	myBorderHoverColor = sf::Color(204, 232, 255);
	myBorderTexture = new sf::Texture();

	// Create border texture
	if (myBorderTexture->create(myWidth, myHeight))
	{
		tempPixels = new sf::Uint8[myWidth * myHeight * 4] { 0 };

		for (int i = 0; i < myWidth * myHeight * 4; i += 4)
		{
			int tempY = (i / 4) / myWidth;
			int tempX = (i / 4) - myWidth * tempY;

			// Only add pixels to the buffer if it is along the border
			if (tempX == 0 || tempX == myWidth - 1 || tempY == 0 || tempY == myHeight - 1)
			{
				tempPixels[i] = myBorderHoverColor.r; // red
				tempPixels[i + 1] = myBorderHoverColor.g; // green
				tempPixels[i + 2] = myBorderHoverColor.b; // blue
				tempPixels[i + 3] = myBorderHoverColor.a; // alpha
			}
		}

		myBorderTexture->update(tempPixels);

		myBorderSprite = sf::Sprite(*myBorderTexture);
		myBorderSprite.setPosition(GetPosition());
	}
	else
	{
		std::cout << "Error creating texture" << std::endl;
	}
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
		aWindow->draw(myBorderSprite);
	}
	else
	{

	}
}