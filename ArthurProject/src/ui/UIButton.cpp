#include "UIButton.h"
#include "SFML/Window/Mouse.hpp"
#include "core/Window.h"

UIButton::UIButton(const sf::Vector2f& aPosition, Node* aParent, UIText* aText, const int& aWidth, const int& aHeight, const sf::Color& aButtonColor, void(*anOnClick)())
	: myWidth(aWidth), myHeight(aHeight), myButtonColor(aButtonColor), myOnClick(anOnClick), UIElement(aPosition, aParent)
{
	myRectangle = sf::IntRect((int)myPosition.x, (int)myPosition.y, myWidth, myHeight);
	myButtonShape = sf::RectangleShape(sf::Vector2f((float)myWidth, (float)myHeight));
	myButtonShape.setFillColor(myButtonColor);
	myButtonShape.setPosition(myPosition);

	float tempTextScaleX = (float)myWidth / aText->GetTextWidth();
	float tempTextScaleY = (float)myHeight / aText->GetTextHeight();
	float tempHeaviestScale = tempTextScaleX < tempTextScaleY ? tempTextScaleX : tempTextScaleY;

	aText->SetFontSize(tempHeaviestScale * aText->GetFontSize());
	AddChild(aText);
}

void UIButton::OnUpdate()
{
	//myText.SetPosition(myPosition);
	//myText.SetFontPosition(myPosition);
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
	UIElement::OnUpdate();
}

void UIButton::OnRender(sf::RenderWindow* aWindow)
{
	// Draw the background button rectangle
	aWindow->draw(myButtonShape);

	// Draw the text on the button
	UIElement::OnRender(aWindow);
}