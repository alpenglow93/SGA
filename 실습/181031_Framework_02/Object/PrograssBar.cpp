#include "stdafx.h"
#include "PrograssBar.h"


PrograssBar::PrograssBar(wstring frontFile, wstring backFile, float maxGauge)
{
	front = new Sprite(frontFile);
	back = new Sprite(backFile);

	curGauge = this->maxGauge = maxGauge;
}

PrograssBar::~PrograssBar()
{
	SAFE_DELETE(front);
	SAFE_DELETE(back);
}

void PrograssBar::Update()
{
	front->Position(position);
	front->Scale(scale.x * curGauge / maxGauge, scale.y);
	front->Update();

	back->Position(position);
	back->Scale(scale);
	back->Update();
}

void PrograssBar::Render()
{
	back->Render();
	front->Render();
}

void PrograssBar::SetGauge(float current, float total)
{
	if (total != 0.0f) maxGauge = total;

	curGauge = current;

	if (curGauge > maxGauge) curGauge = maxGauge;
	if (curGauge < 0.0f) curGauge = 0.0f;
}

void PrograssBar::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void PrograssBar::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void PrograssBar::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void PrograssBar::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}
