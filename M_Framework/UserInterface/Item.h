#pragma once

const wstring ItemPath = _Texture + L"RPG_inventory_icons/";

enum class ItemType
{
	Empty = 0,
	Weapon,
	Head,
	Body
};
struct ItemInfo
{
	ID3D11ShaderResourceView* Image; 
	wstring TexturePath;

	wstring Name;
	ItemType Type;
	int MaxStack;
	int CurrentStack;

	ItemInfo()
	{
		Image = NULL;
		TexturePath = L"";
		Name = L"";
		Type = ItemType::Empty;
		MaxStack = 0;
		CurrentStack = 0;
	}
	ItemInfo(ItemInfo* info)
	{
		Image = info->Image;
		TexturePath = info->TexturePath;
		Name = info->Name;
		Type = info->Type;
		MaxStack = info->MaxStack;
		CurrentStack = info->CurrentStack;
	}
	bool operator== (ItemInfo* info) 
	{
		bool b = true;
		b &= Type == info->Type;
		b &= this->Name == info->Name;

		return b;
	}
	bool operator++()
	{
		CurrentStack++;
		if (CurrentStack > MaxStack)
		{
			CurrentStack = MaxStack;
			return false;
		}
		return true;
	}
	bool operator--()
	{
		CurrentStack--;
		if (CurrentStack < 0)
		{
			return false;
		}
		return true;
	}
	ItemInfo* operator+= (ItemInfo* info)
	{
		this->CurrentStack += info->CurrentStack;
		if (this->CurrentStack >= this->MaxStack)
		{
			int temp;
			temp = this->CurrentStack - this->MaxStack;
			info->CurrentStack = temp;
		}
		else
		{
			SAFE_DELETE(info);
		}
		return this, info;
	}
};
static map<wstring, ItemInfo*> worldItem;