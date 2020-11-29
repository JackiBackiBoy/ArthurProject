#include "UIText.h"
#include "Managers/AssetManager.h"
#include <ui/UIButton.h>

UIText::UIText(const sf::Vector2f& aPosition, Node* aParent, const std::string& aText, const sf::Color& aColor, const std::string& aFontName, const int& aFontSize, bool aButtonTextFlag)
	: myText(aText),myColor(aColor), myFontSize(aFontSize), myButtonTextFlag(aButtonTextFlag), UIElement(aPosition, aParent)
{
	// Load desired font
	myFont = &AssetManager::GetFont(aFontName);

	UpdateText();
}

void UIText::OnUpdate()
{
	//SetFontPosition(GetPosition());
	if (!myButtonTextFlag)
	{
		myRawText->setPosition(GetPosition());
	}
	UIElement::OnUpdate();
}

void UIText::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(*myRawText);
	UIElement::OnRender(aWindow);
}

void UIText::UpdateText()
{
	myRawText = new sf::Text(sf::String(myText), *myFont);
	myRawText->setCharacterSize(myFontSize);
	myRawText->setFillColor(myColor);

	// Position the text correctly
	if (!myButtonTextFlag)
	{
		myRawText->setPosition(sf::Vector2f(GetPosition().x, GetPosition().y - myRawText->getGlobalBounds().top));
	}
}
