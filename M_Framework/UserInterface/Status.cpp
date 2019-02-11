#include "stdafx.h"
#include "Status.h"
#include "./Inventory.h"
#include "./Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Components/Collider/BoxCollider.h"
#include "./Components/Materials/TextureShader.h"
Status* Status::instance = NULL;

Status* Status::Get()
{
	if (instance == NULL)
		instance = new Status;

	return instance;
}

void Status::Delete()
{
	SAFE_DELETE(instance);
}

void Status::Update()
{
	if (Input->GetKeyDown('S'))
		Active();

	if (bShow)
	{
		background->Update();
	}
}

void Status::Render()
{
	if (bShow)
	{
		shader->Texture(backgroundImage);
		background->Render();

		ShowItem(head, headObj);
		ShowItem(body, bodyObj);
		ShowItem(weapon, weaponObj);
	}
}

void Status::ShowItem(ItemInfo* item, QuadObject* obj)
{
	if (item->Type == ItemType::Empty)
	{
		shader->Texture(backgroundImage);
	}
	else
	{
		shader->Texture(item->Image);
	}
	obj->Render();
}

bool Status::IsOverlapBackground()
{
	return backgroundCollder->IsOverlapWithMouse(camera);
}

ItemInfo * Status::EquipItem(ItemInfo * item)
{
	//장비 , 장착 아이템 반화 , 장비 아이템 확인 
	ItemInfo* temp = NULL;

	if (item == NULL) return temp; //추가 

	switch (item->Type)
	{
		case ItemType::Body:
		{
			temp = body;
			body = item;
		}
		break;
		case ItemType::Head:
		{
			temp = head;
			head = item;
		}
		break;
		case ItemType::Weapon:
		{
			temp = weapon;
			weapon = item;
		}
		break;
	}
	return temp;
}

Status::Status()
{
	background = new QuadObject;

	headObj = new QuadObject;
	bodyObj = new QuadObject;
	weaponObj = new QuadObject;

	shader = Materials::Get()->Load<TextureShader>(L"Sprite.hlsl");
	backgroundImage = Sprites::Load(_Texture + L"Empty.png");

	background->SetMaterial(shader);
	headObj->SetMaterial(shader);
	bodyObj->SetMaterial(shader);
	weaponObj->SetMaterial(shader);

	backTrans = background->GetComponent<Transform>();
	backTrans->SetWorldPosition(desc.Width / 4, desc.Height / 2);
	backTrans->Scale(4, 6);

	background->GetComponent<Transform>()->AddChild(
		headObj->GetComponent<Transform>());
	headObj->GetComponent<Transform>()->SetWorldPosition(0, 30);

	background->GetComponent<Transform>()->AddChild(
		bodyObj->GetComponent<Transform>());
	bodyObj->GetComponent<Transform>()->SetWorldPosition(0, 0);

	background->GetComponent<Transform>()->AddChild(
		weaponObj->GetComponent<Transform>());
	weaponObj->GetComponent<Transform>()->SetWorldPosition(32, 15);

	backgroundCollder = background->GetComponent<BoxCollider>();
	headCollider = headObj->GetComponent<BoxCollider>();
	bodyCollider = bodyObj->GetComponent<BoxCollider>();
	weaponCollider = weaponObj->GetComponent<BoxCollider>();

	head = new ItemInfo;
	body = new ItemInfo;
	weapon = new ItemInfo;
}


Status::~Status()
{
	SAFE_DELETE(background);
	SAFE_DELETE(headObj);
	SAFE_DELETE(bodyObj);
	SAFE_DELETE(weaponObj);

	SAFE_DELETE(head);
	SAFE_DELETE(body);
	SAFE_DELETE(weapon);
}

Shader * Status::GetMaterial(wstring name)
{
	return nullptr;
}

void Status::SetCamera(Camera * camera)
{
	this->camera = camera;
}
