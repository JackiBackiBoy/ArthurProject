#pragma once
#include <vector>
#include <functional>
class Event
{

private:
	std::vector<std::function<void()>> myListeners;
public:
	void Invoke();
	void AddListener(std::function<void()> aListener);
	void RemoveListener(std::function<void()> aListener);


};