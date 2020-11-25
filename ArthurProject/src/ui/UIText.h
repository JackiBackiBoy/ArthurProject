#ifndef UI_TEXT_HEADER
#define UI_TEXT_HEADER

#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText() : UIElement({ 0, 0 }) {};
	UIText(const std::string& aText, const sf::Vector2f& aPosition, const std::string& aFontName, const int& aFontSize);

	inline sf::Text* GetRawText() { return myRawText; }

private:
	std::string myText;
	sf::Text* myRawText;
	sf::Font* myFont;
};

#endif