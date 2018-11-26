#pragma once
#include "./Render/Shader.h"
class Line
{
private:
	Vertex * vertices;
	ID3D11Buffer* vertexBuffer;
	const UINT VertexCount = 2;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	float rotate;

public:
	Line();
	~Line();

	void Update(Shader* shader);
	void Render(Shader* shader);

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Rotation(float angle);

private:
	void CreateVertexBuffer();
};

