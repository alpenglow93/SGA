#pragma once
#include "./Singleton/SingletonBase.h"
class Sprite
{
public:
	Sprite(wstring file, 
		D3DXVECTOR2 offset = D3DXVECTOR2(0,0),
		D3DXVECTOR2 size = D3DXVECTOR2(0,0));
	~Sprite();

	void Set(int slot);

	ID3D11ShaderResourceView* Texture() { return texture; }
	D3DXVECTOR2 Size() { return size; }
	D3DXVECTOR2 Offset() { return offset; }
private:

	wstring fileName;

	ID3D11ShaderResourceView* texture;
	D3DX11_IMAGE_INFO info;

	D3DXVECTOR2 offset;
	D3DXVECTOR2 size;
};




class Sprites : SingletonBase<Sprites>
{
public:
	Sprites();
	~Sprites();

	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);
	static D3DX11_IMAGE_INFO Info(wstring file);
private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* Srv = NULL; //이미지 데이터
		D3DX11_IMAGE_INFO Info = { 0 };
	};

	static map<wstring, SpriteDesc> descMap;
};