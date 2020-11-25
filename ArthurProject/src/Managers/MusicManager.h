#pragma once
#include <string>
#include "SFML/Audio.hpp"

class MusicManager
{
public:
	static void TransitionTo(std::string aString);
	static void Stop();
	static void Resume();

private:
	static void TransitionThread();
	static sf::Music myMusic[];
	static int myCurrentMusicIndex;
	static float myTransitionPercent;
	static bool myTransitioningFlag;
	static int GetOtherMusicIndex();
	static float myTransitionTime;
	static sf::Clock myTransitionThreadClock;
};

