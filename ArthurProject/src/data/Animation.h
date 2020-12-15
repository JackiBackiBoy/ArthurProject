#pragma once
#include "SaveLoad.h"
#include <string>
#include <vector>
#include <SFML\System\Vector2.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>

struct AnimationFrame
{
	sf::Vector2i Origin;
	sf::Vector2i Size;
	float Time;
	AnimationFrame(sf::Vector2i anOrigin, sf::Vector2i aSize, float aTime) : Origin(anOrigin), Size(aSize), Time(aTime)
	{
	}
};

struct Animation
{
	std::string TexturePath;
	std::vector<AnimationFrame> Frames;
	int FrameCount;

	void LoadFromFile(std::string aPath)
	{
		Frames = std::vector<AnimationFrame>();
		FrameCount = 0;

		char* cwd = _getcwd(0, 0); // **** microsoft specific ****
		std::string tempStartPath(cwd);
		std::free(cwd);


		std::string text;
		std::ifstream tempFile;
		tempFile.open(tempStartPath + "/" + aPath);
		std::string tempSegment;
		std::vector<std::string> tempSplit;

		//Get each frame
		while (std::getline(tempFile, tempSegment, ';'))
		{
			tempSplit.push_back(tempSegment);
		}

		std::vector<std::string> tempSplit1;
		std::stringstream tempSs = (std::stringstream)tempSplit[0];
		while (std::getline(tempSs, tempSegment, ','))
		{
			tempSplit1.push_back(tempSegment);
		}
		TexturePath = tempSplit1[0];

		//Add each frame to the list
		std::vector<std::string> tempSplit2;
		for (int i = 1; i < tempSplit.size(); i++)
		{
			tempSplit2.clear();
			std::stringstream tempSs1 = (std::stringstream)tempSplit[i];

			while (std::getline(tempSs1, tempSegment, ','))
			{
				tempSplit2.push_back(tempSegment);
			}

			Frames.push_back(AnimationFrame(sf::Vector2i(std::stoi(tempSplit2[0]), std::stoi(tempSplit2[1])),
				sf::Vector2i(std::stoi(tempSplit2[2]), std::stoi(tempSplit2[3])),
				std::stof(tempSplit2[4])));
			FrameCount++;
		}
	}
};

