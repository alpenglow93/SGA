#include "stdafx.h"
#include "Scene_Inventory.h"
#include "./Objects/QuadObject.h"
#include "./Components/Camera.h"
#include "./Components/Transform.h"
#include "./UserInterface/Status.h"
#include "./UserInterface/Inventory.h"
#include "./UserInterface/UITestPlayer.h"
Scene_Inventory::Scene_Inventory()
{
}

Scene_Inventory::~Scene_Inventory()
{
}

void Scene_Inventory::Init()
{
	UIObject = new Object;
	UICamera = new Camera(UIObject);
	UIObject->PushComponent(UICamera);

	UICamera->Update();
	D3DXMATRIX idx;
	D3DXMatrixIdentity(&idx);

	UICamera->SetViewOrhto(&idx);
	Status::Get()->SetCamera(UICamera);
	Inventory::Get()->SetCamera(UICamera);

	mainCameraComp = mainCamera->GetComponent<Camera>();
	quad = new QuadObject();

	player = new UITestPlayer;
	player->SetCamera(mainCameraComp);
}

void Scene_Inventory::Release()
{
	Inventory::Delete();
	Status::Delete();
	SAFE_DELETE(player);
}

void Scene_Inventory::Update()
{
	mainCamera->GetComponent<Transform>()->DefaultControl2();
	quad->Update();
	Status::Get()->Update();
	Inventory::Get()->Update();
	player->Update();
}

void Scene_Inventory::PreRender()
{

	mainCameraComp->Render();
	{
		quad->Render();
	}
	UICamera->Render();
	{
		player->Render();
		Status::Get()->Render();
		Inventory::Get()->Render();
	}
}

void Scene_Inventory::PostRender()
{
}
