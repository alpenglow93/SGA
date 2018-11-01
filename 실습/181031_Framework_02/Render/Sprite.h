#pragma once
#include "./Render/Shader.h"
class Sprite
{
private:
	wstring filePath;

	VertexPT* vertices;	//출력 좌표 + 이미지 출력 영역
	ID3D11Buffer* vertexBuffer;

private:
	const UINT VertexCount = 6;

	D3DXVECTOR2 position;	//위치
	D3DXVECTOR2 scale;	//크기
	float rotation;

	Shader* shader;	//쉐이더

	ID3D11ShaderResourceView* srv;	//texture;

	//Alpha Blend -> 화면에 출력이 된 + 사용할 Texture에 대한 color를 섞어서 출력을 한다.
	//[0]화면 + [1]이미지
	ID3D11BlendState* blendState[2];

	void CreateBlendState();
private:
	struct VertexUVDesc
	{
		D3DXVECTOR2 offset;
		D3DXVECTOR2 maxFrame;
	}vertexUVData;

	ID3D11Buffer* VertexUVBuffer;
	ID3D11SamplerState* samplerState;
	
	void CreateSamplerState();
	void CreateVertexUVBuffer();

public:
	Sprite(wstring file);
	~Sprite();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Rotation(float angle);

	void Offset(float x, float y);
	void Offset(D3DXVECTOR2 offset);

	void MaxFrame(float x, float y);
	void MaxFrame(D3DXVECTOR2 offset);

	void Texture(wstring file);	//이미지 교체

	ID3D11ShaderResourceView* Texture() { return srv; }

	void Update();
	void Render();


};

///////////////////////////////////////////////////////////////////////////

class Sprites
{
private:
	friend class Sprite;

private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* Srv = NULL;	//이미지 데이터
	};

	static map<wstring, SpriteDesc> descMap;
private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);
};