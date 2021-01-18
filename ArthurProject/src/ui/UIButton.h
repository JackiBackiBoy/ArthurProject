#ifndef UI_BUTTON_HEADER
#define UI_BUTTON_HEADER

#include "UIText.h"
#include <functional>

class UIButton : public UIElement
{
public:
	UIButton(const sf::Vector2f& aPosition, const std::string& aName, UIText* aText, const int& aWidth, const int& aHeight, const sf::Color& aButtonColor, void(*anOnClick)());
	//UIButton(const sf::Vector2f& aPosition, const std::string& aName, UIText* aText, const int& aWidth, const int& aHeight, const sf::Color& aButtonColor, std::function<void()>& lambda);

	virtual void OnUpdate() override;
	virtual void OnRender(sf::RenderWindow* aWindow) override;

	inline bool GetIsHovered() const { return myIsHovered; }
	inline void SetOnClick(std::function<void()>& aLambda) { myLambda = aLambda; }

	inline int GetWidth() const { return myWidth; }
	inline int GetHeight() const { return myHeight; }
	void SetWidth(const int& aWidth);

protected:
	//virtual void OnHover();

	int myWidth;
	int myHeight;
	void(*myOnClick)();
	std::function<void()> myLambda = []() {};

	UIText* myTextPointer;
	sf::IntRect myRectangle;
	sf::Color myBaseButtonColor;
	sf::Color myButtonColor;
	sf::RectangleShape myButtonShape;
	sf::Color myClickColor;
	sf::Color myHoverColor;

	bool myIsHovered;
};
#endif