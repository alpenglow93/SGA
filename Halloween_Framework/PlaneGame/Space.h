#pragma once
#include "./Render/Sprite.h"
#include "./Object/Rect.h"
#include "./AirPlane.h"
//��� �̹���(sprite), �浹(��¿�), �÷��̾�(�̵�) 
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

