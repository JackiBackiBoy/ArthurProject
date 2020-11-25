#include "UIText.h"
#include "AssetManager.h"

UIText::UIText(const std::string& aText, const sf::Vector2f& aPosition, const std::string& aFontName, const int& aFontSize) : UIElement(aPosition)
{
	// Load desired font
	myFont = &AssetManager::GetFont(aFontName);

	myRawText = new sf::Text(sf::String(aText), *myFont);
	myRawText->setCharacterSize(aFontSize);

	// Position the text correctly
	myRawText->setPosition(sf::Vector2f(myPosition.x, myPosition.y - myRawText->getGlobalBounds().top));
}