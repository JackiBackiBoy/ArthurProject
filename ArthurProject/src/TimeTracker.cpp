#include "TimeTracker.h"

sf::Clock TimeTracker::myClock = sf::Clock();
sf::Time TimeTracker::myTime = sf::Time::Zero;

void TimeTracker::Update()
{
	myTime = myClock.restart();
}

sf::Time TimeTracker::GetTime()
{
	return myTime;
}

float TimeTracker::GetDeltaTime()
{
	return myTime.asSeconds();
}
