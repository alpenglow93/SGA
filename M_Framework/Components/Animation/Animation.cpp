#include "stdafx.h"
#include "Animation.h"
#include "./Components/Materials/TextureShader.h"
#include "./Objects/Object.h"

Animation::Animation(Object* obj)
	: currentClip(-1)
{
	shader = Materials::Get()->Load<TextureShader>(L"Sprite.hlsl");
	obj->SetMaterial(shader);
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
	if (iter == mClips.end()) return; //존재하지 않는다.
	if (currentClip != -1)
	{
		if (vClips[currentClip] == iter->second) return;
		else vClips[currentClip]->Stop();
	}
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

Clip * Animation::GetClip(UINT index)
{
	if (index < vClips.size()) return NULL;

	return vClips[index];
}

Clip * Animation::CurrentClip()
{
	if (currentClip < 0) return NULL;

	return vClips[currentClip];
}

void Animation::Update()
{
	if (currentClip < 0) return;
	vClips[currentClip]->Update();
}

void Animation::Render()
{
	if (currentClip < 0) return;

	shader->Start(
		vClips[currentClip]->CurrentFrame()->Image->Offset());
	shader->End(
		vClips[currentClip]->CurrentFrame()->Image->Size());
	shader->Update();
	vClips[currentClip]->Render(0);
}

void Animation::SetInsfector()
{
}
