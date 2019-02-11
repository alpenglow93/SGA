#include "stdafx.h"
#include "PrograssBar.h"
#include "./Utilities/Math.h"
#include "./Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Components/Materials/TextureShader.h"
PrograssBar::PrograssBar(wstring frontFile, wstring backFile, float maxGauge)
{
	frontImage = new Sprite(frontFile);
	backImage = new Sprite(backFile);

	curGauge = this->maxGauge = maxGauge;
	TextureShader* shader 
		= Materials::Get()->Load<TextureShader>(L"Sprite.hlsl");

	frontObj = new QuadObject;
	frontObj->SetActive(true);
	frontObj->SetMaterial(shader);

	backObj = new QuadObject;
	backObj->SetActive(true);
	backObj->SetMaterial(shader);

	pivotTrans = new Transform;

	frontObj->GetComponent<Transform>()->AttachTo(pivotTrans);
	backObj->GetComponent<Transform>()->AddChild(pivotTrans);
	
	//-1 ~ 1»çÀÌ°ª
	pivot = { 0.0f,0.0f };
}

PrograssBar::~PrograssBar()
{
	SAFE_DELETE(frontObj);
	SAFE_DELETE(backObj);
	SAFE_DELETE(pivotTrans);
}

void PrograssBar::Update()
{
	pivotTrans->Scale(curGauge / maxGauge, 1);
	backObj->Update();
	frontObj->Update();
}

void PrograssBar::Render()
{

	backImage->Set(0);
	backObj->Render();
	frontImage->Set(0);
	frontObj->Render();
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
	backObj->GetComponent<Transform>()->SetWorldPosition(vec);
	pivotTrans->SetLocalPosition
	(
		pivot.x * 50 , 
		pivot.y * 50
	);
	frontObj->GetComponent<Transform>()->SetLocalPosition(
			-pivot.x * 50,
			-pivot.y * 50
	);

}

void PrograssBar::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void PrograssBar::Scale(D3DXVECTOR2 vec)
{
	backObj->GetComponent<Transform>()->Scale(vec);
}

void PrograssBar::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void PrograssBar::Pivot(float x, float y)
{
	pivot.x = Math::Clamp(x, 1.0f, -1.0f);
	pivot.y = Math::Clamp(y, 1.0f, -1.0f);
}

void PrograssBar::Active()
{
}

Shader * PrograssBar::GetMaterial(wstring name)
{
	return nullptr;
}

void PrograssBar::SetCamera(Camera * camera)
{
}
