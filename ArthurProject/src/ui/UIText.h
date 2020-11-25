#ifndef UI_TEXT_HEADER
#define UI_TEXT_HEADER

#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText(const std::string& aText, const sf::Vector2f& aPosition, const std::string& aFontName);

private:
	std::string myText;
	sf::Text myRawText;
	sf::Font myFont;
};

#endif