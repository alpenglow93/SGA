#include "stdafx.h"
#include "Space.h"

Space::Space(AirPlane * link)
	:sprite(NULL)
	, rect(NULL)
	, player(link)
	, offset(0, 0)
{
	sprite = new Sprite(L"Space.png");
	sprite->Position(0, 0);
	sprite->Scale(desc.Width, desc.Height);

	rect = new Rect;
	rect->Position(0, 0);
	rect->Scale(desc.Width, desc.Height);
}

Space::~Space()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(rect);
	//player는 삭제하면 안된다 -> planeMainGame에서 삭제를 하기 때문에
}

void Space::Update()
{
	D3DXVECTOR2 position;
	player->Position(&position);
	offset.x = position.x / desc.Width;
	offset.y = -position.y / desc.Height;

	D3DXVECTOR2 camPos;
	mainCamera->Position(&camPos);

	rect->Position(camPos);
	rect->Update();

	sprite->Position(camPos);
	sprite->Offset(offset);
	sprite->Update();
}

void Space::Render()
{
	sprite->Render();
}
