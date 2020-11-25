#include "UIButton.h"
#include "SFML/Window/Mouse.hpp"
#include "core/Window.h"

UIButton::UIButton(const UIText& aText, const int& aWidth, const int& aHeight, const sf::Color& aButtonColor, void(*anOnClick)())
	: myText(aText), myWidth(aWidth), myHeight(aHeight), myButtonColor(aButtonColor), myOnClick(anOnClick), UIElement(aText.GetPosition())
{
	myRectangle = sf::IntRect((int)myPosition.x, (int)myPosition.y, myWidth, myHeight);
	myButtonShape = sf::RectangleShape(sf::Vector2f((float)myWidth, (float)myHeight));
	myButtonShape.setFillColor(myButtonColor);
	myButtonShape.setPosition(myPosition);

	float tempTextScaleX = (float)myWidth / myText.GetTextWidth();
	float tempTextScaleY = (float)myHeight / myText.GetTextHeight();
	float tempHeaviestScale = tempTextScaleX < tempTextScaleY ? tempTextScaleX : tempTextScaleY;

	myText.SetFontSize(tempHeaviestScale * myText.GetFontSize());
}

void UIButton::OnUpdate()
{
	myText.SetPosition(myPosition);
	myText.SetFontPosition(myPosition);
	myButtonShape.setPosition(myPosition);

	myRectangle = sf::IntRect((int)myPosition.x, (int)myPosition.y, myWidth, myHeight);

	// Hovering detection
	if (myRectangle.contains(sf::Mouse::getPosition(*Window::CurrentWindow->GetRawWindow())))
	{
		// Make the color darker if hovered
		if (!myIsHovered)
		{
			myButtonColor.r /= 2;
			myButtonColor.g /= 2;
			myButtonColor.b /= 2;
			myButtonShape.setFillColor(myButtonColor);

			myIsHovered = true;
		}
	}
	else
	{
		// Restore the color if not hovered
		if (myIsHovered)
		{
			myButtonColor.r *= 2;
			myButtonColor.g *= 2;
			myButtonColor.b *= 2;
			myButtonShape.setFillColor(myButtonColor);

			myIsHovered = false;
		}
	}
}

void UIButton::OnRender(sf::RenderWindow* aWindow)
{
	// Draw the background button rectangle
	aWindow->draw(myButtonShape);

	// Draw the text on the button
	myText.OnRender(aWindow);
}