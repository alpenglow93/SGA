#pragma once
//1개의 동작 

enum class PlayMode
{
	End = 0, Loop, Reverse,
};
struct Frame
{
	float Time; //교체시간 
	Sprite* Image;
	Frame(Sprite* sprite, float time)
	{
		Image = sprite;
		Time = time;
	}
};
class Clip
{

public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f);
	~Clip();

	void AddFrame(Sprite * sprite, float time);

	
	void Speed(float val) { speed = speed; }
	void CurrentFrame(UINT val) { currentFrame = val; }
	Frame* CurrentFrame() { return frames[currentFrame]; }
	bool IsPlaying() { return bPlay; }

	void Play();
	void Play(UINT playFrame);
	void Stop();

	void Update();
	void Render(int slot);

private:
	float length;
	float speed;
	float playTime;

	bool bPlay;
	bool bReverse;

	UINT currentFrame;
	PlayMode mode;
	vector<Frame*> frames;
};

