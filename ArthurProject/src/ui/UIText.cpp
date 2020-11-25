#include "UIText.h"

UIText::UIText(const std::string& aText, const sf::Vector2f& aPosition, const std::string& aFontName) : UIElement(aPosition)
{
	// Load desired font
	myFont = sf::Font();
	
	if (!myFont.loadFromFile(aFontName))
	{
		std::cout << "Error: Could not load the desired font ('" << aFontName << "')" << std::endl;
	}
}