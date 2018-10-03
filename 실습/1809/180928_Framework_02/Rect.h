#pragma once
class Rect
{
private:
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* vertexLayout;
	const UINT VertexCount = 6;

	struct ColorBufferDesc
	{
		D3DXCOLOR color;
	}colorBufferData;

	ID3D11Buffer* colorBuffer;

	void CreateColorBuffer();

public:
	Rect();
	~Rect();

	void Init(ID3D10Blob* vsBlob);
	void SetRectCenterPosition(
		float x, float y, float width, float height);
	void Render();
	void GetRect(float* left, float* right,
		float* top, float* bottom);

	void SetColor(D3DXCOLOR color);

private:
	void CreateVertexBuffer();

	D3DXMATRIX matWorld;	//�̵� ȸ�� ũ���� ������ ����

	D3DXMATRIX matRot;	//ȸ�� ��� (ȸ�� ����)
	D3DXMATRIX matTrans;	//�̵� ��� (�̵� ����)
	D3DXMATRIX matScale;	//ũ�� ��� (ũ�� ����)

	void UpdateWorld();	//

public:
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 position);

	void SetAngle(float angle);

	void SetScale(float x, float y);
	void SetScale(D3DXVECTOR3 scale);
};

