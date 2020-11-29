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
	myBaseButtonColor = myButtonColor;
	myHoverColor = sf::Color(myButtonColor.r / 2, myButtonColor.g / 2, myButtonColor.b / 2);

	float tempTextScaleX = (float)(myWidth * 0.5f) / aText->GetTextWidth();
	float tempTextScaleY = (float)(myHeight * 0.5f) / aText->GetTextHeight();
	float tempHeaviestScale = tempTextScaleX < tempTextScaleY ? tempTextScaleX : tempTextScaleY;

	aText->SetFontSize(tempHeaviestScale * aText->GetFontSize());
	AddChild(aText);

	UIText& tempChild = *GetChild<UIText>(0);

	sf::Vector2f tempButtonCenter = { (float)(myWidth / 2), (float)(myHeight / 2) };
	sf::Vector2f tempTextCenter = { (float)(tempChild.GetTextWidth() / 2), (float)(tempChild.GetTextHeight() / 2) };
	sf::Vector2f tempNewPosition = { tempButtonCenter.x - tempTextCenter.x, tempButtonCenter.y - tempTextCenter.y };

	tempChild.SetFontPosition(GetPosition() + tempNewPosition);
}

void UIButton::OnUpdate()
{
	//myText.SetPosition(myPosition);
	//myText.SetFontPosition(myPosition);

	/*UIText& tempChild = *GetChild<UIText>(0);

	sf::Vector2f tempButtonCenter = { (float)(myWidth / 2), (float)(myHeight / 2) };
	sf::Vector2f tempTextCenter = { (float)(tempChild.GetTextWidth() / 2), (float)(tempChild.GetTextHeight() / 2) };
	sf::Vector2f tempNewPosition = { tempButtonCenter.x - tempTextCenter.x, tempButtonCenter.y - tempTextCenter.y };

	tempChild.SetFontPosition(GetPosition() + tempNewPosition);*/

	myLambda();
	myButtonShape.setPosition(GetPosition());

	myRectangle = sf::IntRect((int)GetPosition().x, (int)GetPosition().y, myWidth, myHeight);

	// Hovering detection
	if (myRectangle.contains(sf::Mouse::getPosition(*Window::CurrentWindow->GetRawWindow())))
	{
		// Make the color darker if hovered
		if (!myIsHovered)
		{
			myButtonColor = myHoverColor;
			myButtonShape.setFillColor(myButtonColor);

			myIsHovered = true;
		}
	}
	else
	{
		// Restore the color if not hovered
		if (myIsHovered)
		{
			myButtonColor = myBaseButtonColor;
			myButtonShape.setFillColor(myButtonColor);

			myIsHovered = false;
		}
	}

	UIElement::OnUpdate();

	UIText& tempChild = *GetChild<UIText>(0);

	sf::Vector2f tempButtonCenter = { (float)(myWidth / 2), (float)(myHeight / 2) };
	sf::Vector2f tempTextCenter = { (float)(tempChild.GetTextWidth() / 2), (float)(tempChild.GetTextHeight() / 2) + tempChild.GetRawText()->getLocalBounds().top };
	sf::Vector2f tempNewPosition = { tempButtonCenter.x - tempTextCenter.x, tempButtonCenter.y - tempTextCenter.y };

	tempChild.SetFontPosition(GetPosition() + tempNewPosition);
}

void UIButton::OnRender(sf::RenderWindow* aWindow)
{
	// Draw the background button rectangle
	aWindow->draw(myButtonShape);

	// Draw the text on the button
	UIElement::OnRender(aWindow);
}