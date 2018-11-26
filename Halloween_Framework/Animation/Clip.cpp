#include "stdafx.h"
#include "Clip.h"

Clip::Clip(PlayMode mode, float speed)
	:mode(mode), speed(speed),
	length(0.0f),playTime(0.0f),
	bPlay(false), currentFrame(0)
{

}

Clip::~Clip()
{
	//foreach -> ó������ ���������� ������� ���� 
	for (Frame* frame : frames)
	{
		SAFE_DELETE(frame);
	}
}

void Clip::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Clip::Position(D3DXVECTOR2 vec)
{
	for (Frame* frame : frames)
		frame->Image->Position(vec);
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 vec)
{
	for (Frame* frame : frames)
	{
		D3DXVECTOR2 scale = frame->Image->Scale();
		frame->Image->Scale(vec.x * scale.x, scale.y * vec.y);
	}
}

void Clip::Rotation(float angle)
{
	for (Frame* frame : frames)
		frame->Image->Rotation(angle);
}

void Clip::AddFrame(Sprite * sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play() //ù ������ ���� ����
{
	playTime = 0.0f;
	currentFrame = 0;
	nextFrame = (currentFrame + 1) % frames.size();

	currentScale = frames[currentFrame]->Image->Scale();
	nextScale = frames[nextFrame]->Image->Scale();

	bReverse = false;
	bPlay = true;
}

void Clip::Play(UINT playFrame) //���� ������ ���� 
{
	playTime = 0.0f;
	currentFrame = playFrame;

	bReverse = false;
	bPlay = true;
}

void Clip::Stop()
{
	bPlay = false;
	currentFrame = frames.size() - 1;
	nextFrame = frames.size() - 1;
}

void Clip::Update()
{
	//���� ���������� �̵� �Ҽ� �ְ� �ð� ��� 

	//�÷��� ���̳�?
	if (bPlay == false) return;

	//�ð� ��� 
	Frame* frame = frames[currentFrame];

	float time1 = frame->Time * speed;
	playTime += Time->Elapsed();

	//ũ�� ����
	D3DXVECTOR2 scale;
	D3DXVec2Lerp(&scale, &currentScale, &nextScale, playTime / time1);
	frame->Image->Scale(scale);

	if (time1 > playTime) return; //��ü�ð��� �ƴϸ� ���� 

	switch (mode)
	{
		case PlayMode::End:
		{
			currentFrame++;
			nextFrame++;
			if (nextFrame >= frames.size()) nextFrame = currentFrame;
			if (currentFrame >= frames.size()){	Stop();	}
		}
		break;
		case PlayMode::Loop:
		{
			currentFrame++;
			nextFrame = (currentFrame + 1) % frames.size();
			currentFrame %= frames.size();
		}
		break;
		case PlayMode::Reverse:
		{
			if (bReverse == false)
			{
				currentFrame++;
				nextFrame++;
				if (nextFrame >= frames.size()) nextFrame = currentFrame;
				if (currentFrame >= frames.size())
				{
					currentFrame--;
					nextFrame = currentFrame -1;
					bReverse = true;
				}
			}
			else
			{
				currentFrame--;
				nextFrame--;
				if (nextFrame <= 0) nextFrame = 0;
				if (currentFrame <= 0)
				{
					currentFrame++;
					nextFrame = currentFrame + 1;
					bReverse = false;
				}
			}
		}
		break;
	}
	playTime = 0.0f;
	currentScale = frames[currentFrame]->Image->Scale();
	nextScale = frames[nextFrame]->Image->Scale();
}

void Clip::Render()
{
	Frame* frame = frames[currentFrame];
	frame->Image->Update();
	frame->Image->Render();
}
