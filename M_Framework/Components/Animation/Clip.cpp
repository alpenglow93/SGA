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
		SAFE_DELETE(frame->Image);
		SAFE_DELETE(frame);
	}
}

void Clip::AddFrame(Sprite* sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play() //ù ������ ���� ����
{
	playTime = 0.0f;
	currentFrame = 0;

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

	if (time1 > playTime) return; //��ü�ð��� �ƴϸ� ���� 

	switch (mode)
	{
		case PlayMode::End:
		{
			currentFrame++;
			if (currentFrame >= frames.size()){	Stop();	}
		}
		break;
		case PlayMode::Loop:
		{
			currentFrame++;
			currentFrame %= frames.size();
		}
		break;
		case PlayMode::Reverse:
		{
			if (bReverse == false)
			{
				currentFrame++;
				if (currentFrame >= frames.size())
				{
					currentFrame--;
					bReverse = true;
				}
			}
			else
			{
				currentFrame--;
				if (currentFrame <= 0)
				{
					currentFrame++;
					bReverse = false;
				}
			}
		}
		break;
	}
	playTime = 0.0f;
}

void Clip::Render(int slot)
{
	Frame* frame = frames[currentFrame];
	frame->Image->Set(slot);
}
