#include "UIText.h"
#include "Managers/AssetManager.h"
#include <ui/UIButton.h>

UIText::UIText(const sf::Vector2f& aPosition, Node* aParent, const std::string& aText, const sf::Color& aColor, const std::string& aFontName, const int& aFontSize)
	: myColor(aColor), myFontSize(aFontSize), UIElement(aPosition, aParent)
{
	// Load desired font
	myFont = &AssetManager::GetFont(aFontName);

	myRawText = new sf::Text(sf::String(aText), *myFont);
	myRawText->setCharacterSize(myFontSize);
	myRawText->setFillColor(aColor);

	// Position the text correctly
	//myRawText->setPosition(sf::Vector2f(GetPosition().x, GetPosition().y - myRawText->getGlobalBounds().top));
}

void UIText::OnUpdate()
{
	//SetFontPosition(GetPosition());
	//myRawText->setPosition(sf::Vector2f(GetPosition().x, GetPosition().y - myRawText->getGlobalBounds().top));
    UIElement::OnUpdate();
}

void UIText::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(*myRawText);
	UIElement::OnRender(aWindow);
}
