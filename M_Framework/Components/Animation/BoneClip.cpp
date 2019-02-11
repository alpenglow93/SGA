#include "stdafx.h"
#include "BoneClip.h"
#include "./Utilities/BinaryFile.h"

BoneClip::BoneClip()
{
	time = 0.0f;
	currentFrame = 0;
	nextFrame = 1;

	result = new FrameData;
}


BoneClip::~BoneClip()
{
}

void BoneClip::Update()
{
	renderFrame.clear();
	if (!bPlay) return;
	if (frames.size() < 2) return;
	time += Time->Elapsed();
	if (time > frames[currentFrame]->time)
	{
		time = 0.0f;
		currentFrame = (currentFrame + 1) % frames.size();
		nextFrame = (currentFrame + 1) % frames.size();
	}
	//0 ~ 1
	float timeFactor = time / frames[currentFrame]->time;
	
	
	for (int i =0; i < frames[currentFrame]->datas.size(); i++)
	{

		FrameData* currentData = frames[currentFrame]->datas[i];
		FrameData* nextData = frames[nextFrame]->datas[i];
		D3DXVECTOR3 p1 = currentData->translation;
		D3DXVECTOR3 p2 = nextData->translation;

		D3DXQUATERNION r1 = currentData->Rotation;
		D3DXQUATERNION r2 = nextData->Rotation;

		D3DXVECTOR3 s1 = currentData->scale;
		D3DXVECTOR3 s2 = nextData->scale;

		D3DXVec3Lerp(&result->translation, &p1, &p2, timeFactor);
		D3DXVec3Lerp(&result->scale, &s1, &s2, timeFactor);
		D3DXQuaternionSlerp(&result->Rotation, &r1, &r2, timeFactor);

		result->MakeTransform();

		renderFrame.push_back(result->frameMatrix);

	}

}

void BoneClip::Render()
{
}

void BoneClip::AddFrameData(Frame* data, float time)
{
	frames.push_back(data);
}

void BoneClip::SaveFile(wstring file)
{
	BinaryWrite* w = new BinaryWrite();
	w->Open(file);

	w->UInt(frames.size());
	for (auto frame : frames)
	{
		w->String(String::ToString(frame->name));
		w->UInt(frame->time);
		w->UInt(frame->datas.size());
		for (auto data : frame->datas)
		{
			w->Data(data->translation, sizeof(float) * 3);
			w->Data(data->Rotation, sizeof(float) * 4);
			w->Data(data->scale, sizeof(float) * 3);
		}
	}
	w->Close();
}

void BoneClip::LoadFile(wstring file)
{
	BinaryRead* r = new BinaryRead();
	r->Open(file);
	{
		UINT frameCount = r->UInt();
		for (int i = 0; i < frameCount; i++)
		{
			Frame* frame = new Frame();
			frame->name = String::ToWString(r->String());
			frame->time = r->UInt();
			UINT dataCount = r->UInt();
			frame->datas.assign(dataCount,new FrameData());
			//int temp 이중 포인터
			//int* -> &temp
			for (int j = 0; j < frame->datas.size(); j++)
			{
				r->Data((void**)&frame->datas[j]->translation, sizeof(float) * 3);
				r->Data((void**)&frame->datas[j]->Rotation, sizeof(float) * 4);
				r->Data((void**)&frame->datas[j]->scale, sizeof(float) * 3);

			}
			this->frames.push_back(frame);
		}
	}
	r->Close();
}
