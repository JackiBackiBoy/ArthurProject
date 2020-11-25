#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <vector>


class AssetManager
{
private:
	static std::map<std::string, sf::Texture> myTextures;
	static std::map<std::string, sf::Font> myFonts;
	static std::map<std::string, sf::SoundBuffer> mySoundBuffers;
	static std::vector<std::string> GetAllFilesInDirectory(std::string aString);
	static void ReplaceAll(std::string& aStringToReplaceIn, std::string aStringToReplace, std::string aStringToReplaceWith);
public:
	~AssetManager();
	static void Init();
	static void Unload();
	static const sf::Texture& GetTexture(std::string aString);
	static const sf::Font& GetFont(std::string aString);
	static const sf::SoundBuffer& GetSoundBuffer(std::string aString);
};

