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
private:
	float length;
	float speed;
	float playTime;

	bool bPlay;

	UINT currentFrame;

	PlayMode mode;

	vector<Frame*> frames;

	bool bReverse;

private:
	UINT nextFrame;

	D3DXVECTOR2 currentScale;
	D3DXVECTOR2 nextScale;


public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f);
	~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);
	
	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Rotation(float angle);

	void AddFrame(Sprite* sprite, float time);
	
	void Speed(float val) { speed = speed; }
	void CurrentFrame(UINT val) { currentFrame = val; }

	D3DXVECTOR2 GetPosition() {
		return frames[currentFrame]->Image->Position();
	}
	bool IsPlaying() { return bPlay; }

	void Play();
	void Play(UINT playFrame);
	void Stop();

	void Update();
	void Render();
};

