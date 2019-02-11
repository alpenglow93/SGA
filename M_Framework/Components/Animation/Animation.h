#pragma once
#include "../Component.h"
#include "Clip.h"
class Animation : public Component
{
private:
	typedef map<wstring, Clip*> MAP_CLIP;
	typedef vector<Clip*> VEC_CLIP;
private:
	MAP_CLIP mClips;
	VEC_CLIP vClips;

	UINT currentClip;

	class TextureShader* shader;


public:
	Animation(class Object* obj);
	~Animation();

	void AddClip(wstring str, Clip* clip);

	void Play(UINT clipNumber);
	void Play(wstring key);

	Clip* GetClip(UINT index);
	Clip* GetClip(wstring key);
	Clip* CurrentClip();

	void Update() override;
	void Render() override;

	// Component을(를) 통해 상속됨
	virtual void SetInsfector() override;
};

