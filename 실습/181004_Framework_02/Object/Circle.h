#pragma once

#define CIRCLESEGMENTS 36
class Circle
{
private:
	D3DXVECTOR3 Center;
	float Radius;

	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* vertexLayout;

	D3DXVECTOR3 position[CIRCLESEGMENTS + 1];	//������ ������ ��

	//�̵�, ȸ��, ũ��
	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;	//�̵� ���
	D3DXMATRIX matScale;	//ũ�� ���
private:
	struct ColorBufferDesc
	{
		D3DXCOLOR color;
	}colorBufferData;

	ID3D11Buffer* colorBuffer;

public:
	Circle();
	~Circle();

	void Init(ID3D10Blob* vsBlob, float radius);
	void Render();
	void SetColor(D3DXCOLOR color);

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 position);

	void SetScale(float scale);

	D3DXMATRIX GetMatrix() { return matWorld; }

	D3DXVECTOR3 GetCenter() { return Center; }
	float GetRadius() { return Radius; }

private:
	void CreateVertexBuffer();
	void CreateColorBuffer();
	void UpdateWorld();
};

