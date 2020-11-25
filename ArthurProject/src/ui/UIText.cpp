#include "UIText.h"
#include "Managers/AssetManager.h"

UIText::UIText(const std::string& aText, const sf::Vector2f& aPosition, const sf::Color& aColor, const std::string& aFontName, const int& aFontSize)
	: myColor(aColor), myFontSize(aFontSize), UIElement(aPosition)
{
	// Load desired font
	myFont = &AssetManager::GetFont(aFontName);

	myRawText = new sf::Text(sf::String(aText), *myFont);
	myRawText->setCharacterSize(myFontSize);
	myRawText->setFillColor(aColor);

	// Position the text correctly
	myRawText->setPosition(sf::Vector2f(myPosition.x, myPosition.y - myRawText->getGlobalBounds().top));
}

void UIText::OnUpdate()
{
	Node::OnUpdate();
}

void UIText::OnRender(sf::RenderWindow* aWindow)
{
	aWindow->draw(*myRawText);

	Node::OnRender(aWindow);
}
