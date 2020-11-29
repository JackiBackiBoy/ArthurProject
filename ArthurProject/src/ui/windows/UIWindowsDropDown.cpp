#include "UIWindowsDropDown.h"

UIWindowsDropDown::UIWindowsDropDown(const std::string& aHeaderTitle, const sf::Vector2f& aPosition, Node* aParent) : UIElement(aPosition, aParent)
{
	myHeaderButton = new UIWindowsButton(aHeaderTitle, { 0, 0 }, this);

	AddButton("Save");
	AddButton("Load");
}


void UIWindowsDropDown::OnUpdate()
{
	UIElement::OnUpdate();
}

void UIWindowsDropDown::OnRender(sf::RenderWindow* aWindow)
{
	myHeaderButton->OnRender(aWindow);
	//UIElement::OnRender(aWindow);
}

void UIWindowsDropDown::AddButton(const std::string& aButtonName, const std::function<void()>* anOnClick)
{
	sf::Vector2f tempCalculatedPos = { (float)10, (float)((myButtons.size() + 1) * 19) };

	myButtons.push_back(new UIWindowsButton(aButtonName, tempCalculatedPos, myHeaderButton));
}
