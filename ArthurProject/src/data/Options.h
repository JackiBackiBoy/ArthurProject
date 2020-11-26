#pragma once
class Options
{
public:
	static void Load();
	static float GetMasterVolume();
	static float GetMusicVolume();
	static float GetSoundEffectVolume();
private:
	static float myMasterVolume;
	static float myMusicVolume;
	static float mySoundEffectVolume;

};

