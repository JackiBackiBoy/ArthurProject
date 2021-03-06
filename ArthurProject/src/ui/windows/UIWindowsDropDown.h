#ifndef UI_WINDOWS_DROP_DOWN_HEADER
#define UI_WINDOWS_DROP_DOWN_HEADER

#include "ui/UIElement.h"
#include "UIWindowsButton.h"

class UIWindowsDropDown : public UIElement
{
public:
	UIWindowsDropDown(const std::string& aHeaderTitle, const sf::Vector2f& aPosition, const std::string& aName);

	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;

	void AddButton(const std::string& aButtonName, std::function<void()> anOnClick = nullptr);

private:
	UIWindowsButton* myHeaderButton;
	std::vector<UIWindowsButton*> myButtons;
	bool myShowMenuFlag;
};
#endif