#include "stdafx.h"
#include "Circle.h"


Circle::Circle()
	:Center(D3DXVECTOR3(0,0,0)),
	Radius(0.0f)
{

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTrans);

	//Degree(도) or Radian
	float angle = (2 * D3DX_PI) / CIRCLESEGMENTS;

	for (int i = 0; i <= CIRCLESEGMENTS; i++)
	{
		position[i] = {
			cosf(angle * i), sinf(angle * i), 0.0f
		};
	}
}


Circle::~Circle()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(vertexLayout);
	SAFE_RELEASE(colorBuffer);
}

void Circle::Init(ID3D10Blob * vsBlob, float radius)
{
	Radius = radius;
	this->CreateVertexBuffer();
	this->CreateColorBuffer();

	HRESULT hr = DEVICE()->CreateInputLayout(
		Vertex::desc,
		Vertex::count,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&vertexLayout
	);
	assert(SUCCEEDED(hr) && "Not Create LayOut");

}

void Circle::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	UINT VertexCount = 108;
	DEVICECONTEXT()->IASetInputLayout(vertexLayout);
	DEVICECONTEXT()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer,
		&stride, &offset);
	DEVICECONTEXT()->Draw(VertexCount, 0);
}

void Circle::SetColor(D3DXCOLOR color)
{
	colorBufferData.color = color;
	DEVICECONTEXT()->UpdateSubresource(
		colorBuffer, 0, NULL, &colorBufferData, 0, 0
	);
	DEVICECONTEXT()->PSSetConstantBuffers(0, 1, &colorBuffer);

}

void Circle::SetPosition(float x, float y)
{
	D3DXMatrixTranslation(&matTrans, x, y, 0);
	this->Center = D3DXVECTOR3(x, y, 0);
	this->UpdateWorld();
}

void Circle::SetPosition(D3DXVECTOR3 position)
{
	this->SetPosition(position.x, position.y);
	//SetPosition(x,y)안에 UpdateWorld()가 있다.
}

void Circle::SetScale(float scale)
{
	this->Radius *= scale;
	D3DXMatrixScaling(&matScale, scale, scale, 1.0f);
}

void Circle::CreateVertexBuffer()
{
	Vertex* vertice = new Vertex[CIRCLESEGMENTS * 3];

	int index = 0;
	for (int i = 0; i < CIRCLESEGMENTS; i++)
	{
		vertice[index++].position = Center +  position[i] * Radius;
		vertice[index++].position = Center;
		vertice[index++].position = Center + position[i + 1] * Radius;
	}
	

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Vertex) * CIRCLESEGMENTS * 3;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertice;

	HRESULT hr = DEVICE()->CreateBuffer(
		&bufferDesc,
		&data, &vertexBuffer);
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");

	SAFE_DELETE_ARRAY(vertice);
}

void Circle::CreateColorBuffer()
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

void Circle::UpdateWorld()
{
	matWorld = matScale * matTrans;
}
