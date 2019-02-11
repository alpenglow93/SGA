#pragma once
#include "IUserInterface.h"
class PrograssBar : public IUserInterface
{
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

	void Pivot(float x, float y);

	// IUserInterface을(를) 통해 상속됨
	virtual void Active() override;
	virtual Shader * GetMaterial(wstring name) override;
	virtual void SetCamera(class Camera * camera) override;

private:
	class QuadObject* frontObj;
	class QuadObject* backObj;
	
	class Transform* pivotTrans;

	class Sprite* frontImage;
	class Sprite* backImage;

	D3DXVECTOR2 pivot;

	float GaugeStep;
	float maxGauge;
	float curGauge;
};

