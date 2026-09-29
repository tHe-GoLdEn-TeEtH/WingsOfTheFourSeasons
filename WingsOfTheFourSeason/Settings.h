#ifndef SETTINGS_H
#define SETTINGS_H
#include <fstream>

bool musicEnabled = true;
bool sfxEnabled = true;

void loadSettings()
{
	std::ifstream file("settings.txt");
	if (!file.is_open())
	{
		return;   // no settings file yet - defaults (both on) stay in place
	}

	int musicVal;
	int sfxVal;
	file >> musicVal;
	file >> sfxVal;

	if (!file.fail())
	{
		musicEnabled = (musicVal == 1);
		sfxEnabled = (sfxVal == 1);
	}

	file.close();
}

void saveSettings()
{
	std::ofstream file("settings.txt");
	file << (musicEnabled ? 1 : 0) << " " << (sfxEnabled ? 1 : 0) << "\n";
	file.close();
}

void playClickSound()
{
	if (sfxEnabled)
	{
		mciSendString("play clicksound from 0", NULL, 0, NULL);
	}

}

void playSeedCollectSound()
{
	if (sfxEnabled)
	{
		mciSendString("play seedsound from 0", NULL, 0, NULL);
	}
}

void playHurtSound()
{
	if (sfxEnabled)
	{
		mciSendString("play hurtsound from 0", NULL, 0, NULL);
	}
}

void startRainSound()
{
	if (sfxEnabled)
	{
		mciSendString("play rainsound repeat", NULL, 0, NULL);
	}
}

void stopRainSound()
{
	mciSendString("stop rainsound", NULL, 0, NULL);
	mciSendString("seek rainsound to start", NULL, 0, NULL);
}

void playThunderSound()
{
	if (sfxEnabled)
	{
		mciSendString("play thundersound from 0", NULL, 0, NULL);
	}
}

void startDramaSound()
{
	if (sfxEnabled)
	{
		mciSendString("play dramasound repeat", NULL, 0, NULL);
	}
}

void stopDramaSound()
{
	mciSendString("stop dramasound", NULL, 0, NULL);
	mciSendString("seek dramasound to start", NULL, 0, NULL);
}

void startWindSound()
{
	if (sfxEnabled)
	{
		mciSendString("play windsound repeat", NULL, 0, NULL);
	}
}

void stopWindSound()
{
	mciSendString("stop windsound", NULL, 0, NULL);
	mciSendString("seek windsound to start", NULL, 0, NULL);
}

void startSpringSound()
{
	if (sfxEnabled)
	{
		mciSendString("play springsound repeat", NULL, 0, NULL);
	}
}

void stopSpringSound()
{
	mciSendString("stop springsound", NULL, 0, NULL);
	mciSendString("seek springsound to start", NULL, 0, NULL);
}

void playShotSound()
{
	if (sfxEnabled)
	{
		mciSendString("play shotsound from 0", NULL, 0, NULL);
	}
}

void playGameOverSound()
{
	if (sfxEnabled)
	{
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}
}

void applyMusicSetting()
{
	if (musicEnabled)
	{
		mciSendString("resume bgsong", NULL, 0, NULL);
	}
	else
	{
		mciSendString("pause bgsong", NULL, 0, NULL);
	}
}

#endif