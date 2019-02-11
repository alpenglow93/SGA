#include "stdafx.h"
#include "Collider.h"
#include "./Objects/Object.h"
#include "./Components/Transform.h"
#include "./Components/Materials/ColorShader.h"
Collider::Collider(Object * obj)
{
	transform = obj->GetComponent<Transform>();
	matertial = Materials::Get()->Load<ColorShader>(L"Effect.hlsl");
	D3DXMatrixIdentity(&World);
}

Collider::~Collider()
{
}

void Collider::Update()
{
}

void Collider::Render()
{
	UINT offset = 0;
	UINT stride = sizeof(Vertex);
	matertial->World(World * transform->World());
	matertial->Render();
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	DEVICECONTEXT()->Draw(vertexCount, 0);
}

void Collider::GetVertexAndWorld(Vertex** OutVertex, UINT & OutVertexCount, D3DXMATRIX & OutWorld)
{
	*OutVertex = vertices;
	OutVertexCount = vertexCount;
	OutWorld = World * transform->World();
}

