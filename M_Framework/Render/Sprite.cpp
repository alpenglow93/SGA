#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(wstring file, D3DXVECTOR2 offset, D3DXVECTOR2 size)
	:fileName(file), offset(offset), size(size)
{
	texture = Sprites::Load(file);
	info = Sprites::Info(file);

	this->offset.x = offset.x/ info.Width;
	this->offset.y = offset.y/ info.Height;
	if (size.x < 1.0f)
		this->size.x = 1.0f;
	else
		this->size.x  = size.x / info.Width;
	if (size.y < 1.0f)
		this->size.y = 1.0f;
	else
		this->size.y  = size.y / info.Height;

}

Sprite::~Sprite()
{
	Sprites::Remove(fileName);
}

void Sprite::Set(int slot)
{
	DEVICECONTEXT()->PSSetShaderResources(slot, 1,&texture);
}

//---------------------------------------------------------------
map<wstring, Sprites::SpriteDesc> Sprites::descMap;

Sprites::Sprites()
{
}

Sprites::~Sprites()
{
	for (pair<wstring, SpriteDesc> temp : descMap)
	{
		SAFE_RELEASE(temp.second.Srv);
	}
}

//이미지가 없으면 새로 생성 or 존재하면 기존에 저장된 이미지를 찾아서 반환
ID3D11ShaderResourceView * Sprites::Load(wstring file)
{
	map<wstring, SpriteDesc>::iterator iter = descMap.find(file);
	if (iter != descMap.end())
	{
		iter->second.RefCount++;
		return iter->second.Srv;
	}
	HRESULT hr;
	D3DX11_IMAGE_INFO info;

	D3DX11GetImageInfoFromFile
	(
		file.c_str(), NULL, &info, &hr
	);
	assert(SUCCEEDED(hr));

	ID3D11ShaderResourceView* srv;
	D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE(), file.c_str(), NULL, NULL, &srv, &hr
	);
	assert(SUCCEEDED(hr) && "Not Create Texture");

	SpriteDesc spriteDesc;
	spriteDesc.RefCount++;
	spriteDesc.Srv = srv;
	spriteDesc.Info = info;
	descMap[file] = spriteDesc;

	return spriteDesc.Srv;
}

void Sprites::Remove(wstring file)
{
	map<wstring, SpriteDesc>::iterator iter = descMap.find(file);
	wstring error = file + L"Texture is not Remove";
	assert(iter != descMap.end() && error.c_str());

	descMap[file].RefCount--;
	if (descMap[file].RefCount < 1)
	{
		SAFE_RELEASE(descMap[file].Srv);
		descMap.erase(file);
	}
}

D3DX11_IMAGE_INFO Sprites::Info(wstring file)
{
	map<wstring, SpriteDesc>::iterator iter = descMap.find(file);
	if (iter != descMap.end())
	{
		return iter->second.Info;
	}
	assert(false);
	return D3DX11_IMAGE_INFO();
}
