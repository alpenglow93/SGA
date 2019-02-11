#include "stdafx.h"
#include "Rect.h"
Rect::Rect()
{
	VertexCount = 4;
	vertices = new VertexPT[VertexCount];

	vertices[0].position = { -50.0f, -50.0f, 0.0f };
	vertices[1].position = { -50.0f,  50.0f, 0.0f };
	vertices[2].position = {  50.0f,  50.0f, 0.0f };
	vertices[3].position = {  50.0f, -50.0f, 0.0f };

	vertices[0].texCoord = { 0.0f, 1.0f };
	vertices[1].texCoord = { 0.0f, 0.0f };
	vertices[2].texCoord = { 1.0f, 0.0f };
	vertices[3].texCoord = { 1.0f, 1.0f };

	IndexCount = 6;
	UINT* Index = new UINT[IndexCount]{ 0,1,2,0,2,3 };

	CreateVertexBuffer(vertices, sizeof(VertexPT) * VertexCount);
	CreateIndexBuffer(Index);
	SAFE_DELETE_ARRAY(Index);
}
Rect::~Rect()
{
	
}


void Rect::Update()
{
	__super::Update();
}

void Rect::Render()
{
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	__super::Render();
}
