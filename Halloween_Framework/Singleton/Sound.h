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

	FMOD::System* system;		// Fmod를 사용하겠다. 
	FMOD::Sound** sounds;		// 플레이하는 파일들
	FMOD::Channel** channels;	// sound를 관리는 녀석들 
public:
	Sound();
	~Sound();

	void Update();

	void AddSound(wstring file, bool bgm = false, bool loop = false);

	//0.0f ~ 1.0f; 
	void Play(wstring file, float volume = 1.0f);
	void Stop(wstring file); //종료 
	void Pause(wstring file); //일시 정지
	void Resume(wstring file); //다시 재생

	bool IsPlaySound(wstring file); //사운드가 플레이 중이냐?
	bool IsPauseSound(wstring file); //일시정지냐 ?
};

#define SOUND Sound::Get()

