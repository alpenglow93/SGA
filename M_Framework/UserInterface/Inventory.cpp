#include "stdafx.h"
#include "Inventory.h"
#include "./Status.h"
#include "./Utilities/BinaryFile.h"
#include "./Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Components/Materials/ColorShader.h"
#include "./Components/Materials/TextureShader.h"
#include "./Components/Collider/BoxCollider.h"
Inventory* Inventory::instance = NULL;

Inventory * Inventory::Get()
{
	if (instance == NULL)
		instance = new Inventory;
	return instance;
}

void Inventory::Delete()
{
	SAFE_DELETE(instance);
}

void Inventory::Update()
{
	if (Input->GetKeyDown('I'))
		Active();

	if (bShow)
	{
		backGround->Update();
		for (int i = 0; i < slots.size(); i++)
		{
			slots[i]->Update();
		}
		Exchange();
		selectTrans->SetWorldPosition(vMouse.x, vMouse.y);
	}
}

void Inventory::Render()
{
	if (!bShow) return;

	slotShader->Texture(backTexture);
	backGround->Render();

	for (int i = 0; i < slots.size(); i++)
	{
		if (items[i]->Type == ItemType::Empty) continue;



		if (selectItem != NULL)
		{
			if (selectIndex == i)
			{
				continue;
			}
		}
		slotShader->Texture(items[i]->Image);
		slots[i]->Render();
		
	}
	if (selectItem != NULL)
	{
		slotShader->Texture(items[selectIndex]->Image);
		selectObject->Render();
	}
	backGround->Insfector();
}

Inventory::Inventory()
{
	status = Status::Get();
	bShow = false;
	//LoadItems();
	backGround = new QuadObject;
	bgTrans = backGround->GetComponent<Transform>();
	
	bgTrans->SetWorldPosition(1000, 400);
	bgTrans->Scale(4, 6);

	slotShader = Materials::Get()->Load<TextureShader>(L"Sprite.hlsl");
	
	backGround->SetMaterial(slotShader);
	backCollider = backGround->GetComponent<BoxCollider>();

	backTexture = Sprites::Load(_Texture + L"Empty.png");

	SetItem();

	selectObject = new QuadObject();
	selectTrans = selectObject->GetComponent<Transform>();
	selectObject->SetMaterial(slotShader);

	selectItem = NULL;
	selectIndex = -1;
}
Inventory::~Inventory()
{
	SaveItems();
	SAFE_DELETE(backGround);
	for (int i = 0; i < slots.size(); i++)
	{
		SAFE_DELETE(slots[i]);
	}

	for (int i = 0; i < items.size(); i++)
	{
		SAFE_DELETE(items[i]);
	}

	SAFE_DELETE(selectObject);
	SAFE_DELETE(selectItem);

}

void Inventory::SetItem()
{
	ItemInfo* item = new ItemInfo;
	item->TexturePath = ItemPath + L"axe.png";
	item->Image = Sprites::Load(item->TexturePath);
	item->MaxStack = 10;
	item->CurrentStack = 1;
	item->Name = L"Axe";
	item->Type = ItemType::Weapon;

	items.push_back(item);
	worldItem[item->Name] = item;

	item = new ItemInfo;
	item->TexturePath = ItemPath + L"Meat.png";
	item->Image = Sprites::Load(item->TexturePath);
	item->MaxStack = 100;
	item->CurrentStack = 1;
	item->Name = L"Meat";
	item->Type = ItemType::Head;

	items.push_back(item);
	worldItem[item->Name] = item;

	item = new ItemInfo;
	item->TexturePath = ItemPath + L"armor.png";
	item->Image = Sprites::Load(item->TexturePath);
	item->MaxStack = 100;
	item->CurrentStack = 1;
	item->Name = L"Armor";
	item->Type = ItemType::Body;

	items.push_back(item);
	worldItem[item->Name] = item;

	int size = items.size();
	for (int i = 0; i < 20 - size;i++)
	{
		items.push_back(new ItemInfo);
	}

	for (int i = 0; i < 20; i++)
	{
		QuadObject* slot = new QuadObject;
		slot->GetComponent<Transform>()->AttachTo(bgTrans);
		slot->GetComponent<Transform>()->SetWorldPosition(
			-30 + 30 * (i % 3), 40 - 30 * (i / 3));
		slot->SetMaterial(slotShader);
		slotsCollider.push_back(slot->GetComponent<BoxCollider>());
		slots.push_back(slot);
	}
}

void Inventory::SaveItems()
{
	BinaryWrite* w = new BinaryWrite;
	w->Open(L"Inventory.Item");
	{
		w->UInt(items.size());
		for (int i = 0; i < items.size();i++)
		{
			w->String(String::ToString(items[i]->TexturePath));
			w->String(String::ToString(items[i]->Name));
			w->UInt((UINT)items[i]->Type);
			w->Int(items[i]->MaxStack);
			w->Int(items[i]->CurrentStack);
		}
	}
	w->Close();

	w->Open(L"WorldItem.List");
	{
		for (pair<wstring, ItemInfo*> item : worldItem)
		{
			w->String(String::ToString(item.first));
			w->String(String::ToString(item.second->TexturePath));
			w->String(String::ToString(item.second->Name));
			w->UInt((UINT)item.second->Type);
			w->Int(item.second->MaxStack);
			w->Int(item.second->CurrentStack);
		}
	}
	w->Close();
	SAFE_DELETE(w);
}

void Inventory::LoadItems()
{
	BinaryRead* r = new BinaryRead;
	if (!r->Open(L"Inventory.Item")) return;
	{
		UINT size = r->UInt();
		for (int i = 0; i < size; i++)
		{
			ItemInfo* info = new ItemInfo;
			info->TexturePath = String::ToWString(r->String());
			info->Image = Sprites::Load(info->TexturePath);
			info->Name = String::ToWString(r->String());
			info->Type = (ItemType)r->UInt();
			info->MaxStack = r->Int();
			info->CurrentStack = r->Int();
		
			items.push_back(info);
		}
	}
	r->Close();
}

void Inventory::Exchange()
{

	if (backCollider->IsOverlapWithMouse(camera))
	{
		for (int i = 0; i < slotsCollider.size(); i++)
		{
			if (slotsCollider[i]->IsOverlapWithMouse(camera))
			{
				if (Input->GetKeyDown(VK_LBUTTON))
				{
					if (items[i]->Type == ItemType::Empty) break;
					selectItem = items[i];
					selectIndex = i;
					break;
				}//Ã³À½ ´­·ÈÀ»‹š 
				if (Input->GetKeyUp(VK_LBUTTON))
				{
					if (selectItem == NULL) break;

					ItemInfo* temp;
					temp = items[selectIndex];
					items[selectIndex] = items[i];
					items[i] = temp;

					selectItem = NULL;
					break;
				}//
			}
		}
	}
	else
	{
		if (Input->GetKeyUp(VK_LBUTTON))
		{
			if (status->IsOverlapBackground())
			{
				ItemInfo* temp = status->EquipItem(selectItem);

				if (temp != NULL)
				{
					if (temp->Type == ItemType::Empty)
					{
						items[selectIndex] = temp;
					}
					else
					{
						for (int i = 0; i < items.size(); i++)
						{
							if (items[i]->Type == ItemType::Empty)
								continue;
							if (items[i]->Name == temp->Name)
							{
								bool b = items[i]++;
								if (!b) items.push_back(new ItemInfo(temp));
								///items[i] += temp;
							}
						}
					}//end of else if(temp->Type != Empty)
					selectItem = NULL;
				}
			}
			else
			{
				selectItem = NULL;
			}
		}
		

	}


}

void Inventory::SetCamera(Camera * camera)
{
	this->camera = camera;
}

Shader * Inventory::GetMaterial(wstring name)
{
	return nullptr;
}
