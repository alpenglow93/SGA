#pragma once
#include "./Render/Shader.h"
class Sprite
{
private:
	VertexPT* vertices;	//출력 좌표 + 이미지 출력 영역
	ID3D11Buffer* vertexBuffer;

private:
	const UINT VertexCount = 6;

	D3DXVECTOR2 position;	//위치
	D3DXVECTOR2 scale;	//크기

	Shader* shader;	//쉐이더

	ID3D11ShaderResourceView* srv;	//texture;

	//Alpha Blend -> 화면에 출력이 된 + 사용할 Texture에 대한 color를 섞어서 출력을 한다.
	//[0]화면 + [1]이미지
	ID3D11BlendState* blendState[2];

	void CreateBlendState();
public:
	Sprite();
	Sprite(wstring file);
	~Sprite();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Update();
	void Render();


};

