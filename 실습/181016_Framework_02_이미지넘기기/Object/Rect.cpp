#include "stdafx.h"
#include "Rect.h"


void Rect::CreateColorBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ColorBufferDesc);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = DEVICE()->CreateBuffer(
		&bufferDesc,
		NULL, &colorBuffer);
	assert(SUCCEEDED(hr) && "Not Create ColorBuffer");
}

Rect::Rect()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matScale);

	Init();
}


Rect::~Rect()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_DELETE_ARRAY(vertices);
}

void Rect::Init()
{
	vertices = new Vertex[VertexCount];

	vertices[0].position = { -0.5f, -0.5f, 0.0f };
	vertices[1].position = { -0.5f, 0.5f, 0.0f };
	vertices[2].position = { 0.5f, -0.5f, 0.0f };

	vertices[3].position = { 0.5f, -0.5f, 0.0f };
	vertices[4].position = { -0.5f, 0.5f, 0.0f };
	vertices[5].position = { 0.5f, 0.5f, 0.0f };

	this->CreateVertexBuffer();
	this->CreateColorBuffer();

	shader = new Shader(L"Effect.hlsl");
	shader->CreateInputLayout(Vertex::desc, Vertex::count);
}

void Rect::Update()
{
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&matTrans,
		position.x + scale.x * 0.5f,
		position.y + scale.y * 0.5f, 1.0f);
}

void Rect::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT()->Draw(VertexCount, 0);
}

void Rect::CreateVertexBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;	//Default ·Î ¼öÁ¤
	bufferDesc.ByteWidth = sizeof(Vertex) * VertexCount;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices;

	HRESULT hr = DEVICE()->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
}


void Rect::GetRect(float * left, float * right, float * top, float * bottom)
{
	*left = vertices[0].position.x;
	*right = vertices[2].position.x;
	*top = vertices[1].position.y;
	*bottom = vertices[3].position.y;
}

void Rect::SetColor(D3DXCOLOR color)
{
	colorBufferData.color = color;
	DEVICECONTEXT()->UpdateSubresource(
		colorBuffer, 0, NULL, &colorBufferData, 0, 0
	);
	DEVICECONTEXT()->PSSetConstantBuffers(0, 1, &colorBuffer);
}

void Rect::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Rect::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Rect::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Rect::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}
