#include "stdafx.h"
#include "Rect.h"


Rect::Rect()
{
}


Rect::~Rect()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(vertexLayout);
	SAFE_DELETE_ARRAY(vertices);
}

void Rect::Init(D3DXCOLOR color, ID3D10Blob* vsBlob)
{
	vertices = new VertexPC[VertexCount];

	for (int i = 0; i < VertexCount;i++)
	{
		vertices[i].color = color;
	}

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(VertexPC) * VertexCount;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	HRESULT hr = DEVICE()->CreateBuffer(
		&bufferDesc,
		NULL, &vertexBuffer);
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");

	hr = DEVICE()->CreateInputLayout(
		VertexPC::desc,
		VertexPC::count,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&vertexLayout
	);
	assert(SUCCEEDED(hr) && "Not Create LayOut");
}

void Rect::SetRectCenterPosition(float x, float y, float width, float height)
{
	float left = x - width / 2;
	float right = x + width / 2;
	float top = y + height / 2;
	float bottom = y - height / 2;
	//왼쪽 상단 삼각형 
	vertices[0].position = D3DXVECTOR3(left, bottom, 0);
	vertices[1].position = D3DXVECTOR3(left, top, 0);
	vertices[2].position = D3DXVECTOR3(right, top, 0);
	//오른쪽 하단 삼각형 
	vertices[3] = vertices[0];
	vertices[4] = vertices[2];
	vertices[5].position = D3DXVECTOR3(right, bottom, 0);

	//VertexBuffer에 데이터 쓰기
	D3D11_MAPPED_SUBRESOURCE resource;
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	
	HRESULT hr = DEVICECONTEXT()->Map(vertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &resource);

	assert(SUCCEEDED(hr) && "Not VertexBuffer Mapping");
	memcpy(resource.pData, vertices, sizeof(VertexPC) * VertexCount);

	DEVICECONTEXT()->Unmap(vertexBuffer, 0);
}

void Rect::Render()
{
	UINT stride = sizeof(VertexPC);
	UINT offset = 0;

	DEVICECONTEXT()->IASetInputLayout(vertexLayout);
	DEVICECONTEXT()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer,
		&stride, &offset);
	DEVICECONTEXT()->Draw(VertexCount, 0);
}

void Rect::CreateVertexBuffer()
{
}

void Rect::GetRect(float * left, float * right, float * top, float * bottom)
{
	*left = vertices[0].position.x;
	*right = vertices[2].position.x;
	*top = vertices[1].position.y;
	*bottom = vertices[5].position.y;
}
