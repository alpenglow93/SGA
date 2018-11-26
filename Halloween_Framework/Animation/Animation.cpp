#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
	: currentClip(-1), position(0,0),rotation(0)
{
}


Animation::~Animation()
{
	for (Clip* clip : vClips)
	{
		SAFE_DELETE(clip);
	}
}

void Animation::AddClip(wstring str, Clip * clip)
{
	vClips.push_back( clip );
	mClips[str] = clip;
}

void Animation::Play(UINT clipNumber)
{
	if (clipNumber == currentClip) return;
	if (currentClip != -1) vClips[currentClip]->Stop();
	currentClip = clipNumber;
	vClips[currentClip]->Play();
}

void Animation::Play(wstring key)
{
	MAP_CLIP::iterator iter = mClips.find(key);
	if (iter->first == key) return;
	if (currentClip != -1) vClips[currentClip]->Stop();

	int count = 0;
	for (Clip* clip : vClips)
	{
		if (clip == iter->second)
		{
			currentClip = count;
			clip->Play();
			break;
		}
		count++;
	}

}

void Animation::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Animation::Position(D3DXVECTOR2 vec)
{
	for (Clip* clip : vClips)
	{
		clip->Position(vec);
	}
}

void Animation::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Animation::Scale(D3DXVECTOR2 scale)
{
	for (Clip* clip : vClips)
		clip->Scale(scale);
}

void Animation::Rotation(float angle)
{
	for (Clip* clip : vClips)
		clip->Rotation(angle);
}

Clip * Animation::GetClip(UINT index)
{
	return vClips[index];
}

Clip * Animation::CurrentClip()
{
	return vClips[currentClip];
}

void Animation::Update()
{
	vClips[currentClip]->Update();
}

void Animation::Render()
{
	vClips[currentClip]->Render();
}
