#include "stdafx.h"
#include "Sound.h"
#include "./Utilities/String.h"


Sound::Sound()
{
	FMOD::System_Create(&system);

	//사운드 채널수 생성
	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	sounds = new FMOD::Sound*[TOTALSOUNDBUFFER];
	channels = new FMOD::Channel*[TOTALSOUNDBUFFER];

	memset(sounds, 0, sizeof(FMOD::Sound*) * TOTALSOUNDBUFFER);
	memset(channels, 0, sizeof(FMOD::Channel*) * TOTALSOUNDBUFFER);
}


Sound::~Sound()
{
	for (auto iter : totalSounds)
	{
		if (iter.second)
		{
			(*iter.second)->release();
			(*iter.second) = NULL;
		}
	}


	if (channels != NULL || sounds != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (channels != NULL)
				if (channels[i]) channels[i]->stop();
			if (sounds != NULL)
				if (sounds[i]) sounds[i]->release();
		}
	}
	SAFE_DELETE_ARRAY(channels);
	SAFE_DELETE_ARRAY(sounds);
	if (system != NULL)
	{
		system->release();
		system->close();
	}
}

void Sound::Update()
{
	system->update();
}
void Sound::AddSound(wstring file, bool bgm, bool loop)
{
	wstring Key = L"./Resources/Sound/" + file;
	string Path = String::ToString(Key);

	if (loop)
	{
		if (bgm) //배경음악
		{
			system->createStream(Path.c_str(), FMOD_LOOP_NORMAL, NULL,
				&sounds[totalSounds.size()]);
		}
		else //효과음
		{
			system->createSound(Path.c_str(), FMOD_LOOP_NORMAL, NULL,
				&sounds[totalSounds.size()]);
		}
	}
	else
	{
		system->createSound(Path.c_str(), FMOD_DEFAULT, NULL,
			&sounds[totalSounds.size()]);
	}
	totalSounds[Key] = &sounds[totalSounds.size()];
}

void Sound::Play(wstring file, float volume)
{
	wstring Path = L"./Resources/Sound/" + file;
	int count = 0;
	for (auto iter : totalSounds)
	{
		if (Path == iter.first)
		{
			system->playSound(FMOD_CHANNEL_FREE,
				*iter.second, false, &channels[count]);
			channels[count]->setVolume(volume);
		}
		count++;
	}
}

void Sound::Stop(wstring file)
{
	wstring Path = L"./Resources/Sound/" + file;
	int count = 0;
	for (auto iter : totalSounds)
	{
		if (Path == iter.first)
		{
			channels[count]->stop();
			break;
		}
		count++;
	}
}

void Sound::Pause(wstring file)
{
	wstring Path = L"./Resources/Sound/" + file;
	int count = 0;
	for (auto iter : totalSounds)
	{
		if (Path == iter.first)
		{
			channels[count]->setPaused(true);
			break;
		}
		count++;
	}
}

void Sound::Resume(wstring file)
{
	wstring Path = L"./Resources/Sound/" + file;
	int count = 0;
	for (auto iter : totalSounds)
	{
		if (Path == iter.first)
		{
			channels[count]->setPaused(false);
			break;
		}
		count++;
	}
}

bool Sound::IsPlaySound(wstring file)
{
	wstring Path = L"./Resources/Sound/" + file;
	bool bPlay = false;
	int count = 0;
	for (auto iter : totalSounds)
	{
		if (Path == iter.first)
		{
			channels[count]->isPlaying(&bPlay);
			break;
		}
		count++;
	}
	return bPlay;
}

bool Sound::IsPauseSound(wstring file)
{
	wstring Path = L"./Resources/Sound/" + file;
	bool bPlay = false;
	int count = 0;
	for (auto iter : totalSounds)
	{
		if (Path == iter.first)
		{
			channels[count]->getPaused(&bPlay);
			break;
		}
		count++;
	}
	return bPlay;
}
