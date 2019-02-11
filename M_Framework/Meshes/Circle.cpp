#include "stdafx.h"
#include "Circle.h"


Circle::Circle(float radius)
	:Center(D3DXVECTOR3(0,0,0)),
	Radius(radius)
{
	//Degree(µµ) or Radian
	float angle = (float)(2 * D3DX_PI) / CIRCLESEGMENTS;
	vertices = new VertexPT[CIRCLESEGMENTS + 2];
	VertexCount = CIRCLESEGMENTS + 2;
	
	vertices[0].position = Center;
	vertices[0].texCoord = { 0.5f,0.5f };
	for (int i = 0; i <= CIRCLESEGMENTS  ; i++)
	{
		position[i] = {cosf(angle * i), sinf(angle * i), 0.0f};
		vertices[i + 1].position = position[i] * Radius;
		vertices[i + 1].texCoord = { position[i].x, position[i].y };
	}
	IndexCount = CIRCLESEGMENTS * 3;
	UINT* indices = new UINT[IndexCount];

	for (int i = 0; i < CIRCLESEGMENTS; i++)
	{
		indices[3 * i + 0] = 0;
		indices[3 * i + 1] = i + 2;
		indices[3 * i + 2] = i + 1;
	}
	this->CreateVertexBuffer(vertices, VertexCount);
	this->CreateIndexBuffer(indices);
	Meshes::AddMesh(this);
}

Circle::~Circle()
{

}

void Circle::Update()
{
	__super::Update();
}

void Circle::Render()
{
	__super::Render();
}
