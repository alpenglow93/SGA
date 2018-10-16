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

	D3DXMATRIX matWorld;	//�̵� ȸ�� ũ���� ������ ����

	D3DXMATRIX matRot;	//ȸ�� ��� (ȸ�� ����)
	D3DXMATRIX matTrans;	//�̵� ��� (�̵� ����)
	D3DXMATRIX matScale;	//ũ�� ��� (ũ�� ����)

	void UpdateWorld();	//

public:
	D3DXMATRIX GetWorld() { return matWorld; }
};

