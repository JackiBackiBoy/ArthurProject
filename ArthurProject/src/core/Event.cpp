#include "Event.h"

void Event::Invoke()
{
	for (int i = 0; i < myListeners.size(); i++)
	{
		myListeners[i]();
	}
}

void Event::AddListener(std::function<void()> aListener)
{
	myListeners.push_back(aListener);
}

void Event::RemoveListener(std::function<void()> aListener)
{
	//myListeners.erase(std::find(myListeners.begin(), myListeners.end(), aListener));
}
