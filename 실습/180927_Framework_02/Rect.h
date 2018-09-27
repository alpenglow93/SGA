#pragma once
class Rect
{
private:
	VertexPC* vertices;
	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* vertexLayout;
	const UINT VertexCount = 6;
public:
	Rect();
	~Rect();

	void Init(D3DXCOLOR color, ID3D10Blob* vsBlob);
	void SetRectCenterPosition(
		float x, float y, float width, float height);
	void Render();
	void GetRect(float* left, float* right, float* top, float* bottom);

private:
	void CreateVertexBuffer();
};

