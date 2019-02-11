#include "stdafx.h"
#include "Scene_FrustumCulling.h"
#include "Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Components/Collider/BoxCollider.h"
#include "./Components/Collider/SphereCollider.h"
#include "./UserInterface/PrograssBar.h"
#include "./Utilities/Ray.h"
float Scene_FrustumCulling::respwanTime = 0.0f;
float Scene_FrustumCulling::maxHp = 100.0f;
float Scene_FrustumCulling::currentHp = 100.0f;
int Scene_FrustumCulling::currentBulletCount = 10;

Scene_FrustumCulling::Scene_FrustumCulling()
{
}


Scene_FrustumCulling::~Scene_FrustumCulling()
{
}

void Scene_FrustumCulling::Init()
{
	//무명 함수
	//int a = 10;
	//[a]() {int b = a; }
	//[캡쳐]반환값(매개변수){ 함수 내용}
	gameObjects.push_back(new QuadObject);
	collider = new SphereCollider(gameObjects[0]);
	gameObjects[0]->PushComponent(collider);
	check = new SphereCollider(new Object);
	check2 = new SphereCollider(new Object);
	check2->SetRadius(10);
	boxCollider = gameObjects[0]->GetComponent<BoxCollider>();

	gameObjects[0]->EnableActive = [](Object* obj)  // false -> true
	{
		obj->GetComponent<Transform>()->SetWorldPosition(
			rand() % (int)desc.Width, rand() % (int)desc.Height);
		obj->GetComponent<Transform>()->Rotation(rand() % 360);
		currentHp = maxHp;
		respwanTime = 0.0f;
	};
	gameObjects[0]->DisableActive = [](Object* obj) //true-> false;
	{
		respwanTime = 0.0f;
	};
	gameObjects[0]->ActiveUpdate = [](Object* obj)
	{
		if (currentHp < 0.0f)
			obj->SetActive(false);
	};
	gameObjects[0]->NotActiveUpdate = [](Object* obj)
	{
		respwanTime += Time->Elapsed();
		if (respwanTime > 1.0f)
			obj->SetActive(true);
	};
	gameObjects[0]->SetActive(true);
	bar = new PrograssBar(
		_Texture + L"ProgressBarFront.bmp",
		_Texture + L"ProgressBarBack.bmp",
		100.0f
	);
	bar->Pivot(-1.0f, 0);
	bar->Scale(2.0f, 0.1f);
	bar->Position(desc.Width / 2, desc.Height / 2);
	curGauge = 100.0f;
	ray = new Ray();
	ray->SetOrigin(desc.Width / 2, desc.Height / 2);
}

void Scene_FrustumCulling::Release()
{
	SAFE_DELETE(ray);
	SAFE_DELETE(bar);
	SAFE_DELETE(check);
	SAFE_DELETE(check2);

}

void Scene_FrustumCulling::Update()
{
	if (Input->GetKey(VK_LEFT))
		curGauge -= 1.0f;
	if (Input->GetKey(VK_RIGHT))
		curGauge += 1.0f;

	bar->SetGauge(curGauge);
	bar->Update();
	ray->SetTarget(vMouse.x, vMouse.y);
	ray->Update();
	check->Update();
	check2->Update();
}

void Scene_FrustumCulling::PreRender()
{
	bar->Render();
	ray->Render();
	check->Render();
	check2->Render();
	
}

void WaitReload(bool* b)
{
	float time = 0.0f;
	while (time < 10.0f)
	{
		time += 0.000001f;
	}
	*b = false;
	Scene_FrustumCulling::currentBulletCount = 10;
}


void Scene_FrustumCulling::PostRender()
{
	RECT rc = { 100,0, desc.Width, desc.Height };
	D3DXVECTOR2 point;
	if (ray->Raycast(collider, &point, NULL))
	{
		DirectWrite::RenderText(L"충돌", rc);
		check->SetCenter(point.x, point.y);
	}
	else
	{
		DirectWrite::RenderText(L"안충돌", rc);
	}
	rc = { 100, 20, (LONG)desc.Width, (LONG)desc.Height };

	char str[32];
	sprintf_s(str, "%.0f", currentHp);
	DirectWrite::RenderText(L"Hp : " + String::ToWString(str), rc);
	rc = { 100, 40, (LONG)desc.Width, (LONG)desc.Height };
	if (ray->Raycast(boxCollider, &point))
	{
		DirectWrite::RenderText(L"충돌", rc);
		check2->SetCenter(point.x, point.y);
		if (Input->GetKeyDown(VK_LBUTTON))
		{
			if (bReload == true) return;
			currentBulletCount--;
			if (currentBulletCount <= 0)
			{
				bReload = true;
				th1 = new thread(WaitReload, &bReload);
			}
			
			if (gameObjects[0]->GetActive())
			{
				currentHp -= 10.0f;
			}
		}
	}
	else
	{
		DirectWrite::RenderText(L"안충돌", rc);
	}
	rc = { 100, 60, (LONG)desc.Width, (LONG)desc.Height };
	//char str[8];
	wsprintfA(str, "%d", currentBulletCount);
	DirectWrite::RenderText(String::ToWString(str), rc);

}



void Scene_FrustumCulling::EA()
{
	gameObjects[0]->GetComponent<Transform>()->SetWorldPosition(
		rand() % (int)desc.Width, rand() % (int)desc.Height);
	respwanTime = 0.0f;
}

void Scene_FrustumCulling::DA()
{
	respwanTime = 0.0f;
}

void Scene_FrustumCulling::AU()
{
	respwanTime += Time->Elapsed();
	gameObjects[0]->GetComponent<Transform>()->DefaultControl();
	if (respwanTime > 3.0f)
	{
		gameObjects[0]->SetActive(false);
	}
}

void Scene_FrustumCulling::DU()
{
	respwanTime += Time->Elapsed();
	if (respwanTime > 1.0f)
		gameObjects[0]->SetActive(true);
}
