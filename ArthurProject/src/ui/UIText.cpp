#include "UIText.h"
#include "Managers/AssetManager.h"
#include <ui/UIButton.h>

UIText::UIText(const sf::Vector2f& aPosition, const std::string& aName, const std::string& aText, const sf::Color& aColor, const std::string& aFontName, const int& aFontSize)
	: myColor(aColor), myFontSize(aFontSize), UIElement(aPosition, aName)
{
	// Load desired font
	myFont = &AssetManager::GetFont(aFontName);

	myRawText = new sf::Text(sf::String(aText), *myFont);
	myRawText->setCharacterSize(myFontSize);
	myRawText->setFillColor(aColor);

	myRawText->setPosition(GetPosition());

	// Position the text correctly
	//myRawText->setPosition(sf::Vector2f(GetPosition().x, GetPosition().y - myRawText->getGlobalBounds().top));
}

void UIText::OnUpdate()
{
	myRawText->setPosition(GetPosition());

	sf::Color tempTextColor = myRawText->getFillColor();
	myRawText->setFillColor({ tempTextColor.r, tempTextColor.g, tempTextColor.b, (sf::Uint8)myAlpha });

	//SetFontPosition(GetPosition());
	//myRawText->setPosition(sf::Vector2f(GetPosition().x - GetTextWidth(), GetPosition().y));
	//SetFontPosition({ GetPosition().x, GetPosition().y });
    UIElement::OnUpdate();
}

void UIText::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(*myRawText);
	UIElement::OnRender(aWindow);
}

void UIText::SetPosition(const sf::Vector2f& aPosition)
{
	Node::SetPosition(aPosition);
	myRawText->setPosition(myPosition);
}
