#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"
#include "./Render/Sprite.h"

//����
enum class LOC	//�ٵϵ� ����
{
	BLACK,
	WHITE,
	NONE
};
enum class PLAYER	//���
{
	BLACK,
	WHITE
};

struct tagLoc
{
	LOC state;
	Sprite* sprite;
	Rect* rect;	//���x	//RECT -> WINAPI �� �ڵ������� ��������ִ� RECT
};

class MainGame
{
private:
	tagLoc loc[20][20];
	int click = 0;
	PLAYER winPlayer;

	Sprite* winLogo;
	bool bGameOver = false;

	Sprite* sprite;

public:
	MainGame();
	~MainGame();

	void Init();	//�ʱ�ȭ
	void Release();	//����
	void Update();	//Ű�Է�, ���, ���콺
	void Render();	//���
	void CheckWinPlayer();
};

