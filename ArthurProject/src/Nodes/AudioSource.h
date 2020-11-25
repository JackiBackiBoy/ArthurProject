#pragma once
#include "Node.h"
#include <string>
#include "SFML/Audio.hpp"

class AudioSource:public Node
{
public:
	void Play(std::string aString);
	AudioSource() : Node(sf::Vector2f(0, 0), nullptr) {};
	AudioSource(const sf::Vector2f& aPosition, Node* aParent);

	inline void OnUpdate() override { Node::OnUpdate(); };
	inline void OnRender(sf::RenderWindow* aWindow) override { Node::OnRender(aWindow); };

private:
	std::vector<sf::Sound> mySounds;
};

