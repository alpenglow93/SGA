#pragma once
#include "./Render/Sprite.h"
#include "./Object/Rect.h"
#include "./AirPlane.h"
//배경 이미지(sprite), 충돌(출력용), 플레이어(이동) 
class Space
{
private:
	Sprite * sprite;
	Rect * rect;
	AirPlane * player;
	D3DXVECTOR2 offset;
public:
	Space(AirPlane* link);
	~Space();

	void Update();
	void Render();
	Rect* GetRect() { return rect; }
};

