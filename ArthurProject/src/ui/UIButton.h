#ifndef UI_BUTTON_HEADER
#define UI_BUTTON_HEADER

#include "UIText.h"

class UIButton : public UIElement
{
public:
	UIButton() : UIElement({ 0, 0 }, "UIButton") {};
	UIButton(const sf::Vector2f& aPosition, const std::string& aName, UIText* aText, const int& aWidth, const int& aHeight, const sf::Color& aButtonColor, void(*anOnClick)());

	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;

private:
	int myWidth;
	int myHeight;
	void(*myOnClick)();
	bool myPressedFlag;

	sf::IntRect myRectangle;
	sf::Color myButtonColor;
	sf::RectangleShape myButtonShape;

	bool myIsHovered;
};
#endif