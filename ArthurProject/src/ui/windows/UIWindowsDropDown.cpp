#include "UIWindowsDropDown.h"
#include "math/MathFunctions.h"

UIWindowsDropDown::UIWindowsDropDown(const std::string& aHeaderTitle, const sf::Vector2f& aPosition, const std::string& aName) : UIElement(aPosition, aName)
{
	myHeaderButton = new UIWindowsButton(aHeaderTitle, { 0, 0 }, aName + "Btn");
	myButtons = std::vector<UIWindowsButton*>();
	AddButton("New");
	AddButton("Save");
	AddButton("Load");
	AddButton("Load");
	AddButton("Load");
	AddButton("Load");
	AddButton("Load");
	AddButton("Load");
}


void UIWindowsDropDown::OnUpdate()
{
	//float t = myHeaderButton->GetAlpha();
	//myHeaderButton->Alpha() = MathFunctions::Lerp(myHeaderButton->Alpha(), 255.0f, 0.1f);
	//float u = myHeaderButton->GetAlpha();

	myHeaderButton->OnUpdate();

	std::vector<UIWindowsButton*> tempAllButtons = myHeaderButton->GetChildrenOfType<UIWindowsButton>();

	// Determine whether any of the buttons are hovered. In that case, show the drop-down menu
	if (myHeaderButton->GetIsHovered() || std::find_if(tempAllButtons.begin(), tempAllButtons.end(), [](const auto& val) { return val->GetIsHovered(); }) != tempAllButtons.end())
	{
		for (size_t i = 0; i < tempAllButtons.size(); i++)
		{
			tempAllButtons[i]->SetPosition({ MathFunctions::Lerp(tempAllButtons[i]->GetPosition().x, 30, 0.03f / (i + 1)), tempAllButtons[i]->GetPosition().y });
			tempAllButtons[i]->SetAlpha(MathFunctions::Lerp(tempAllButtons[i]->GetAlpha(), 255, 0.003f));
		}
	}
	else
	{
		for (size_t i = 0; i < tempAllButtons.size(); i++)
		{
			tempAllButtons[i]->SetPosition({ MathFunctions::Lerp(tempAllButtons[i]->GetPosition().x, 0, 0.03f / (i + 1)), tempAllButtons[i]->GetPosition().y });
			tempAllButtons[i]->SetAlpha(MathFunctions::Lerp(tempAllButtons[i]->GetAlpha(), 0, 0.003f));
		}
	}

	UIElement::OnUpdate();
}

void UIWindowsDropDown::OnRender(sf::RenderWindow* aWindow)
{
	myHeaderButton->OnRender(aWindow);

	UIElement::OnRender(aWindow);
}

void UIWindowsDropDown::AddButton(const std::string& aButtonName, const std::function<void()>* anOnClick)
{
	sf::Vector2f tempCalculatedPos = { (float)0, (float)((myButtons.size() + 1) * 19) };
	myHeaderButton->AddChild(new UIWindowsButton(aButtonName, tempCalculatedPos, aButtonName));
	myButtons.push_back(myHeaderButton->GetChild<UIWindowsButton>(aButtonName));
}
