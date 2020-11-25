#include "MusicManager.h"
#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>

sf::Music MusicManager::myMusic[2];
int MusicManager::myCurrentMusicIndex = 0;
float MusicManager::myTransitionTime = 2;
float MusicManager::myTransitionPercent = 0;
sf::Clock MusicManager::myTransitionThreadClock = sf::Clock();
bool MusicManager::myLoopingFlag = true;

void MusicManager::TransitionTo(std::string aString)
{
	myCurrentMusicIndex = GetOtherMusicIndex();
	myMusic[myCurrentMusicIndex].setVolume(0);
	Start(aString);


	myTransitionPercent = 0;
	myTransitionThreadClock.restart();
	std::thread t1(TransitionThread);


	t1.join();

}

void MusicManager::TransitionThread()
{
	while (myTransitionPercent < 100)
	{
		myTransitionPercent += myTransitionThreadClock.restart().asSeconds()*100 / myTransitionTime;
		myMusic[myCurrentMusicIndex].setVolume(myTransitionPercent);
		myMusic[GetOtherMusicIndex()].setVolume(100 - myTransitionPercent);
	}
	myMusic[myCurrentMusicIndex].setVolume(100);
}

void MusicManager::Stop()
{
	myMusic[myCurrentMusicIndex].stop();
}
void MusicManager::Start(std::string aString)
{
	myMusic[myCurrentMusicIndex].openFromFile("Assets/DPL Music/" + aString + ".wav");
	myMusic[myCurrentMusicIndex].play();
}
void MusicManager::Pause()
{
	myMusic[myCurrentMusicIndex].pause();

}
void MusicManager::Resume()
{
	myMusic[myCurrentMusicIndex].play();
}

void MusicManager::SetLoopingFlag(bool aFlag)
{
	myLoopingFlag = aFlag;
}

bool MusicManager::GetLoopingFlag()
{
	return myLoopingFlag;
}

int MusicManager::GetOtherMusicIndex()
{
	return (myCurrentMusicIndex == 0 ? 1 : 0);
}


