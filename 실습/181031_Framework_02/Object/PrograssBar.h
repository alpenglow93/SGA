#pragma once
#include "./Render/Sprite.h"
class PrograssBar
{
private:
	Sprite * back;
	Sprite* front;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;	//처음 크기만

	float maxGauge;
	float curGauge;
public:
	PrograssBar(wstring frontFile, wstring backFile, float maxGauge);
	~PrograssBar();

	void Update();
	void Render();

	void SetGauge(float current, float total = 0.0f);
	
	void Position(D3DXVECTOR2 vec);
	void Position(float x, float y);

	void Scale(D3DXVECTOR2 vec);
	void Scale(float x, float y);
};

