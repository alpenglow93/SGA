#pragma once
#include "./Render/Shader.h"
#include "./Line.h"
class Rect
{
private:
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;
	const UINT VertexCount = 6;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	float rotate;

	Shader* shader;

	Line* line;
	RECT AABB;

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
	
	void GetRect(float* left, float* right, float* top, float* bottom);
	RECT GetRect();

	D3DXVECTOR2 GetPosition() { return position; }
	D3DXVECTOR2 GetScale() { return scale; }
	void SetColor(D3DXCOLOR color);

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Rotation(float angle);

private:
	void CreateVertexBuffer();

	D3DXMATRIX matWorld; // �̵� ȸ�� ũ�� �� ������ ����

	D3DXMATRIX matRot;   //ȸ�� ��� (ȸ�� ����)
	D3DXMATRIX matTrans; //�̵� ��� (�̵� ����)
	D3DXMATRIX matScale; //ũ�� ��� (ũ�� ����)

public:
	D3DXMATRIX GetWorld() { return matWorld; }
	void GizmoRender();

};

