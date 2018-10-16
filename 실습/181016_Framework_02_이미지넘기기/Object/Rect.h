#pragma once
#include "./Render/Shader.h"
class Rect
{
private:
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;
	const UINT VertexCount = 6;

	Shader* shader;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

private:
	struct ColorBufferDesc
	{
		D3DXCOLOR color;
	}colorBufferData;

	ID3D11Buffer* colorBuffer;

	void CreateColorBuffer();

public:
	Rect();
	~Rect();

	void Init();

	void Update();
	void Render();

	void GetRect(float* left, float* right,	float* top, float* bottom);
	D3DXVECTOR2 GetPosition() { return position; }

	void SetColor(D3DXCOLOR color);

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

private:
	void CreateVertexBuffer();

	D3DXMATRIX matWorld;	//이동 회전 크기의 데이터 보유

	D3DXMATRIX matRot;	//회전 행렬 (회전 값만)
	D3DXMATRIX matTrans;	//이동 행렬 (이동 값만)
	D3DXMATRIX matScale;	//크기 행렬 (크기 값만)

	void UpdateWorld();	//

public:
	D3DXMATRIX GetWorld() { return matWorld; }
};

