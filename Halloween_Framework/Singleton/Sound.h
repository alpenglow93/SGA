#pragma once
#include "./SingletonBase.h"
#include "./_Libraries/FMOD/inc/fmod.hpp"
#pragma comment(lib, "./_Libraries/FMOD/lib/fmodex_vc.lib")

#define EXTARCHANNELBUFFER 5
#define SOUNDBUFFER 20

#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTARCHANNELBUFFER)

class Sound : public SingletonBase<Sound>
{
protected:
	map<wstring, FMOD::Sound**> totalSounds;

	FMOD::System* system;		// Fmod�� ����ϰڴ�. 
	FMOD::Sound** sounds;		// �÷����ϴ� ���ϵ�
	FMOD::Channel** channels;	// sound�� ������ �༮�� 
public:
	Sound();
	~Sound();

	void Update();

	void AddSound(wstring file, bool bgm = false, bool loop = false);

	//0.0f ~ 1.0f; 
	void Play(wstring file, float volume = 1.0f);
	void Stop(wstring file); //���� 
	void Pause(wstring file); //�Ͻ� ����
	void Resume(wstring file); //�ٽ� ���

	bool IsPlaySound(wstring file); //���尡 �÷��� ���̳�?
	bool IsPauseSound(wstring file); //�Ͻ������� ?
};

#define SOUND Sound::Get()

