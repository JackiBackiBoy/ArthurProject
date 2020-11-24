#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>

class AssetManager
{
private:
	static std::vector<std::string, sf::Texture> myTextures;
	static std::vector<sf::Font> myFonts;
public:
	void Init();
	void Unload();
	sf::Texture GetTexture(std::string aString);
	sf::Font GetFont(std::string aString);
};

