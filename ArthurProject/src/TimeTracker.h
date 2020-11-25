#pragma once
#include <SFML/System/Clock.hpp>
class TimeTracker
{
private:
	static sf::Clock myClock;
	static sf::Time myTime;
public:
	static void Update();
	static sf::Time GetTime();
	static float GetDeltaTime();
};
