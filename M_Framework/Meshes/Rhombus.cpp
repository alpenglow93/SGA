#include "stdafx.h"
#include "Rhombus.h"


Rhombus::Rhombus()
{
	VertexCount = 6;
	vertices = new VertexPT[VertexCount];
	
	vertices[0].position = D3DXVECTOR3(-50, 0, 0);//왼쪽
	vertices[1].position = D3DXVECTOR3(  0,25, 0);//윗
	vertices[2].position = D3DXVECTOR3(50, 0, 0); //오른쪽

	vertices[3].position = D3DXVECTOR3(-50, 0, 0);//왼쪽
	vertices[4].position = D3DXVECTOR3(50, 0, 0); //오른쪽
	vertices[5].position = D3DXVECTOR3(0, -25, 0);//아래
	//일반 타일 이미지
	vertices[0].texCoord = D3DXVECTOR2(0, 1);
	vertices[1].texCoord = D3DXVECTOR2(0, 0);
	vertices[2].texCoord = D3DXVECTOR2(1, 0);

	vertices[3].texCoord = D3DXVECTOR2(0, 1);
	vertices[4].texCoord = D3DXVECTOR2(1, 0);
	vertices[5].texCoord = D3DXVECTOR2(1, 1);

	CreateVertexBuffer(vertices, sizeof(VertexPT) * VertexCount);

	//아이소 타일로 사용시
	//vertices[0].texCoord = D3DXVECTOR2(0, 0.5f); //왼쪽 
	//vertices[1].texCoord = D3DXVECTOR2(0.5f, 0); //윗
	//vertices[2].texCoord = D3DXVECTOR2(1, 0.5f); //오른쪽

	//vertices[3].texCoord = D3DXVECTOR2(0, 0.5f); //왼쪽
	//vertices[4].texCoord = D3DXVECTOR2(1, 0.5f); //오른쪽
	//vertices[5].texCoord = D3DXVECTOR2(0.5f, 1);    //아래


}


Rhombus::~Rhombus()
{
}

void Rhombus::Update()
{
	__super::Update();
}

void Rhombus::Render()
{
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	__super::Render();
}
