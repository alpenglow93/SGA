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
	//foreach -> 처음부터 마지막까지 순서대로 동작 
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

void Clip::Play() //첫 프레임 부터 시작
{
	playTime = 0.0f;
	currentFrame = 0;

	bReverse = false;
	bPlay = true;
}

void Clip::Play(UINT playFrame) //지정 프레임 이후 
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
	//다음 프레임으로 이동 할수 있게 시간 계산 

	//플레이 중이냐?
	if (bPlay == false) return;

	//시간 계산 
	Frame* frame = frames[currentFrame];

	float time1 = frame->Time * speed;
	playTime += Time->Elapsed();

	if (time1 > playTime) return; //교체시간이 아니면 종료 

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
