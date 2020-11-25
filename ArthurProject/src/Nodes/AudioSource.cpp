#include "AudioSource.h"
#include "Managers/AssetManager.h"


void AudioSource::Play(std::string aString)
{
	mySounds.push_back(sf::Sound(AssetManager::GetSoundBuffer(aString)));
	mySounds.back().play();
	GetPosition();
}

AudioSource::AudioSource(const sf::Vector2f& aPosition, Node* aParent):Node(aPosition, aParent)
{
	mySounds = std::vector<sf::Sound>();
}


