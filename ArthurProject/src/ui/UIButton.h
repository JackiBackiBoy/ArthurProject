#ifndef UI_BUTTON_HEADER
#define UI_BUTTON_HEADER

#include "UIText.h"

class UIButton : public UIElement
{
public:
	UIButton() : UIElement({ 0, 0 }) {};
	UIButton(const UIText& aText, const int& aWidth, const int& aHeight, const sf::Color& aButtonColor, void(*anOnClick)());

	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;

private:
	UIText myText;
	int myWidth;
	int myHeight;
	void(*myOnClick)();

	sf::IntRect myRectangle;
	sf::Color myButtonColor;
	sf::RectangleShape myButtonShape;

	bool myIsHovered;
};
#endif