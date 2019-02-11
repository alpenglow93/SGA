#include "stdafx.h"
#include "Rhombus.h"


Rhombus::Rhombus()
{
	VertexCount = 6;
	vertices = new VertexPT[VertexCount];
	
	vertices[0].position = D3DXVECTOR3(-50, 0, 0);//����
	vertices[1].position = D3DXVECTOR3(  0,25, 0);//��
	vertices[2].position = D3DXVECTOR3(50, 0, 0); //������

	vertices[3].position = D3DXVECTOR3(-50, 0, 0);//����
	vertices[4].position = D3DXVECTOR3(50, 0, 0); //������
	vertices[5].position = D3DXVECTOR3(0, -25, 0);//�Ʒ�
	//�Ϲ� Ÿ�� �̹���
	vertices[0].texCoord = D3DXVECTOR2(0, 1);
	vertices[1].texCoord = D3DXVECTOR2(0, 0);
	vertices[2].texCoord = D3DXVECTOR2(1, 0);

	vertices[3].texCoord = D3DXVECTOR2(0, 1);
	vertices[4].texCoord = D3DXVECTOR2(1, 0);
	vertices[5].texCoord = D3DXVECTOR2(1, 1);

	CreateVertexBuffer(vertices, sizeof(VertexPT) * VertexCount);

	//���̼� Ÿ�Ϸ� ����
	//vertices[0].texCoord = D3DXVECTOR2(0, 0.5f); //���� 
	//vertices[1].texCoord = D3DXVECTOR2(0.5f, 0); //��
	//vertices[2].texCoord = D3DXVECTOR2(1, 0.5f); //������

	//vertices[3].texCoord = D3DXVECTOR2(0, 0.5f); //����
	//vertices[4].texCoord = D3DXVECTOR2(1, 0.5f); //������
	//vertices[5].texCoord = D3DXVECTOR2(0.5f, 1);    //�Ʒ�


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
