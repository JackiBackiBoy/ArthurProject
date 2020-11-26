#include "Options.h"
#include "data/SaveLoad.h"


float Options::myMasterVolume = 100;
float Options::myMusicVolume = 100;
float Options::mySoundEffectVolume = 100;

void Options::Load()
{
	//Defaults
	if (SaveLoad::Load("MVol") == "")
		SaveLoad::Save("MVol", std::to_string(myMasterVolume));
	if (SaveLoad::Load("SEffVol") == "")
		SaveLoad::Save("SEffVol", std::to_string(mySoundEffectVolume));
	if (SaveLoad::Load("MusicVol") == "")
		SaveLoad::Save("MusicVol", std::to_string(myMusicVolume));



	myMasterVolume = std::stof(SaveLoad::Load("MVol"));
	myMasterVolume = std::stof(SaveLoad::Load("SEffVol"));
	myMasterVolume = std::stof(SaveLoad::Load("MusicVol"));
}

float Options::GetMasterVolume()
{
	return myMasterVolume;
}

float Options::GetMusicVolume()
{
	return myMusicVolume;
}

float Options::GetSoundEffectVolume()
{
	return mySoundEffectVolume;
}
