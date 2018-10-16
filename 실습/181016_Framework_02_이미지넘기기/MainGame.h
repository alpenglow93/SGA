#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"
#include "./Render/Sprite.h"

//오목
enum class LOC	//바둑돌 색상
{
	BLACK,
	WHITE,
	NONE
};
enum class PLAYER	//결과
{
	BLACK,
	WHITE
};

struct tagLoc
{
	LOC state;
	Sprite* sprite;
	Rect* rect;	//출력x	//RECT -> WINAPI 에 자동적으로 만들어져있는 RECT
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

	void Init();	//초기화
	void Release();	//삭제
	void Update();	//키입력, 계산, 마우스
	void Render();	//출력
	void CheckWinPlayer();
};

