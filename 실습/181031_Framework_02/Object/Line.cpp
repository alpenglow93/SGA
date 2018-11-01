#include "stdafx.h"
#include "Line.h"


Line::Line()
{
	vertices = new Vertex[VertexCount];
	vertices[0].position = { 0.0f, 0.0f, 0.0f };
	vertices[1].position = { 0.0f, 1.0f, 0.0f };

	this->CreateVertexBuffer();
}


Line::~Line()
{
	SAFE_DELETE_ARRAY(vertices);
}

void Line::Update(Shader * shader)
{
	D3DXMATRIX S, R, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	D3DXMatrixRotationZ(&R, rotate);

	shader->SetWVPData(S * R * T);
}

void Line::Render(Shader * shader)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	shader->SetShader();

	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT()->Draw(VertexCount, 0);
}

void Line::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Line::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Line::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Line::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void Line::Rotation(float angle)
{
	rotate = angle;
}

void Line::CreateVertexBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //Defulat·Î ¼öÁ¤
	bufferDesc.ByteWidth = sizeof(Vertex) * VertexCount;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices;

	HRESULT hr = DEVICE()->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
}
