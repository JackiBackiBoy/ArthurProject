#ifndef UI_TEXT_HEADER
#define UI_TEXT_HEADER

#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText() : UIElement() {};
	UIText(const sf::Vector2f& aPosition, Node* aParent, const std::string& aText, const sf::Color& aColor, const std::string& aFontName, const int& aFontSize);
	inline sf::Text* GetRawText() { return myRawText; }

	void OnUpdate() override;
	void OnRender(sf::RenderWindow* aWindow) override;

	inline int GetTextWidth() const { return myRawText->getGlobalBounds().width; }
	inline int GetTextHeight() const { return myRawText->getGlobalBounds().height - myRawText->getGlobalBounds().top; }
	inline int GetFontSize() const { return myFontSize; }
	inline void SetFontSize(const int& aFontSize) const { myRawText->setCharacterSize(aFontSize); }
	inline void SetFontPosition(const sf::Vector2f& aPosition) { myRawText->setPosition(aPosition); };

private:
	std::string myText;
	sf::Text* myRawText;
	sf::Font* myFont;
	sf::Color myColor;
	int myFontSize;
};
#endif