#include "MusicManager.h"
#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>

sf::Music MusicManager::myMusic[2];
int MusicManager::myCurrentMusicIndex = 0;
float MusicManager::myTransitionTime = 2;
float MusicManager::myTransitionPercent = 0;
sf::Clock MusicManager::myTransitionThreadClock = sf::Clock();

void MusicManager::TransitionTo(std::string aString)
{
	myCurrentMusicIndex = GetOtherMusicIndex();
	myMusic[myCurrentMusicIndex].openFromFile("Assets/DPL Music/" + aString + ".wav");
	myMusic[myCurrentMusicIndex].setVolume(0);
	myMusic[myCurrentMusicIndex].play();


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
}

void MusicManager::Resume()
{
}

int MusicManager::GetOtherMusicIndex()
{
	return (myCurrentMusicIndex == 0 ? 1 : 0);
}


