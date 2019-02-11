#include "stdafx.h"
#include "Line.h"
#include "./Components/Transform.h"
Line::Line()
{
	VertexCount = 2;
	vertices = new VertexPT[VertexCount];
	vertices[0].position = { 0.0f,0.0f,0.0f };
	vertices[1].position = { 0.0f,1.0f,0.0f };

	this->CreateVertexBuffer(vertices,sizeof(VertexPT) * VertexCount);
}


Line::~Line()
{
	
}

void Line::Update()
{
	__super::Update();
}

void Line::Render()
{
	__super::Render();
}

void Line::Direction(float x, float y, class Transform* trans)
{
	Direction(D3DXVECTOR2( x, y), trans);
}

void Line::Direction(D3DXVECTOR2 vec, class Transform* trans)
{
	trans->LookDirection(vec);
}
