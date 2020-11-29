#ifndef UI_WINDOWS_BUTTON_HEADER
#define UI_WINDOWS_BUTTON_HEADER

#include "ui/UIButton.h"

class UIWindowsButton : public UIButton
{
public:
	UIWindowsButton(const std::string& aText, const sf::Vector2f& aPosition, Node* aParent);

	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;

private:
	sf::Color myBorderHoverColor;
	sf::Color myBorderClickColor;
	sf::Sprite myBorderSprite;
	sf::Uint8* tempPixels;
	sf::Texture* myBorderTexture;
};
#endif