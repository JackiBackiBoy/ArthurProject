#ifndef UI_BUTTON_HEADER
#define UI_BUTTON_HEADER

#include "UIText.h"

class UIButton : public UIElement
{
public:
	UIButton() : UIElement({ 0, 0 }) {};
	//UIButton(const std::string& aText, const sf::Vector2f& aPosition, )
	UIButton(const UIText& aText);
};
#endif