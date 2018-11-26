#pragma once
#include "Clip.h"
class Animation
{
private:
	typedef map<wstring, Clip*> MAP_CLIP;
	typedef vector<Clip*> VEC_CLIP;
private:
	MAP_CLIP mClips;
	VEC_CLIP vClips;

	UINT currentClip;

	D3DXVECTOR2 position;
	float rotation;

public:
	Animation();
	~Animation();

	void AddClip(wstring str, Clip* clip);

	void Play(UINT clipNumber);
	void Play(wstring key);

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 scale);

	void Rotation(float angle);
	float Rotation() { return rotation; }

	Clip* GetClip(UINT index);
	Clip* CurrentClip();

	void Update();
	void Render();

};

