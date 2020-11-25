#include "AssetManager.h"
#include <filesystem>
#include <regex>

std::map<std::string, sf::Texture> AssetManager::myTextures = std::map<std::string, sf::Texture>();
std::map<std::string, sf::Font> AssetManager::myFonts = std::map<std::string, sf::Font>();
std::map<std::string, sf::SoundBuffer> AssetManager::mySoundBuffers = std::map<std::string, sf::SoundBuffer>();

std::string myPathOrigin = "Assets";
AssetManager::~AssetManager()
{
}
void AssetManager::Init()
{
	std::cout << "All assets:" << std::endl;
	//Loop through all asset files
	for (std::string s : GetAllFilesInDirectory("./" + myPathOrigin))
	{
		//If file is tagged DontPreLoad, skip file
		if (s.find("DPL") != std::string::npos) continue;

		//Display Current file in console
		std::cout << s << std::endl;

		//Remove "Assets\\" from s
		s.erase(0, myPathOrigin.length() + 3);
		//Replace all \\ with /
		ReplaceAll(s, "\\", "/");

		//If File is a png file
		if (s.find(".png") != std::string::npos)
		{
			//Remove ".png"
			s.erase(s.length() - 4, 4);

			//add a spot with the index [filename]
			myTextures.emplace(s, sf::Texture());
			//Set texture in map
			myTextures[s].loadFromFile(myPathOrigin + "/" + s + ".png");
		}
		//If File is a ttf file
		else if (s.find(".ttf") != std::string::npos)
		{
			//Remove ".ttf"
			s.erase(s.length() - 4, 4);

			//add a spot with the index [filename]
			myFonts.emplace(s, sf::Font());
			//Set Font in map
			myFonts[s].loadFromFile(myPathOrigin + "/" + s + ".ttf");
		}
		//If File is a wav file
		else if (s.find(".wav") != std::string::npos)
		{
			//Remove ".wav"
			s.erase(s.length() - 4, 4);

			//add a spot with the index [filename]
			mySoundBuffers.emplace(s, sf::SoundBuffer());
			//Set SoundBuffer in map
			mySoundBuffers[s].loadFromFile(myPathOrigin + "/" + s + ".wav");
		}



	}
}

void AssetManager::ReplaceAll(std::string& aStringToReplaceIn, std::string aStringToReplace, std::string aStringToReplaceWith)
{
	size_t index = 0;
	while (index < aStringToReplaceIn.length())
	{
		/* Locate the substring to replace. */
		index = aStringToReplaceIn.find(aStringToReplace, index);
		if (index == std::string::npos) break;

		/* Make the replacement. */
		aStringToReplaceIn.replace(index, aStringToReplaceWith.length(), aStringToReplaceWith);

		/* Advance index forward so the next iteration doesn't pick it up as well. */
		index += aStringToReplaceWith.length();
	}
}

std::vector<std::string> AssetManager::GetAllFilesInDirectory(std::string aString)
{
	std::vector<std::string> tempFiles = std::vector<std::string>();
	for (auto& file : std::filesystem::directory_iterator{ aString })  //loop through the current folder
	{
		if (std::filesystem::is_directory(file))
		{
			for (std::string f : GetAllFilesInDirectory(file.path().string()))
			{
				tempFiles.push_back(f);
			}
		}
		else
		{
			tempFiles.push_back(file.path().string());
		}
	}
	return tempFiles;
}

const sf::Texture& AssetManager::GetTexture(std::string aString)
{
	return myTextures[aString];
}

const sf::Font& AssetManager::GetFont(std::string aString)
{
	return myFonts[aString];
}

const sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string aString)
{
	return mySoundBuffers[aString];
}
