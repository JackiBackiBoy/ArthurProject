#include "AudioSource.h"
#include "Managers/AssetManager.h"
#include "data/Options.h"


void AudioSource::Play(std::string aString)
{

	mySounds.push_back(sf::Sound(AssetManager::GetSoundBuffer(aString)));
	mySounds.back().setVolume(Options::GetSoundEffectVolume());
	mySounds.back().play();
}

AudioSource::AudioSource(const sf::Vector2f& aPosition, const std::string& aName) : Node(aPosition, aName)
{
	mySounds = std::vector<sf::Sound>();
}


