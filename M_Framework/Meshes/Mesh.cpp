#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
	: vertexBuffer(NULL), vertices(NULL), VertexCount(0),
	 IndexBuffer(NULL)
{
}

Mesh::~Mesh()
{
	SAFE_DELETE_ARRAY(vertices);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(IndexBuffer);
}

void Mesh::Update()
{
}

void Mesh::Render()
{
	UINT offset = 0;
	UINT stride = sizeof(VertexPT);

	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	DEVICECONTEXT()->DrawIndexed(IndexCount, 0, 0);
}

void Mesh::CreateVertexBuffer(void * data, UINT size)
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //Defulat·Î ¼öÁ¤
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	resourceData.pSysMem = data;

	HRESULT hr = DEVICE()->CreateBuffer(&bufferDesc, &resourceData, &vertexBuffer);
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
}

void Mesh::CreateIndexBuffer(UINT * data)
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(UINT) * IndexCount;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	resourceData.pSysMem = data;


	HRESULT hr = DEVICE()->CreateBuffer(&bufferDesc, &resourceData, &IndexBuffer);
	assert(SUCCEEDED(hr));
}

////////////////////////////////////////////////////////////////
vector<Mesh*> Meshes::meshes;

void Meshes::Delete()
{
	for (Mesh* mesh : meshes)
	{
		SAFE_DELETE(mesh);
	}
}
