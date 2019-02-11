#pragma once

#define VERTEX_XY DXGI_FORMAT_R32G32_FLOAT
#define VERTEX_XYZ DXGI_FORMAT_R32G32B32_FLOAT
#define VERTEX_XYZW DXGI_FORMAT_R32G32B32A32_FLOAT


struct Vertex
{
	D3DXVECTOR3 position;
	Vertex()
	{
		this->position = D3DXVECTOR3(0, 0, 0);
	}
	Vertex(D3DXVECTOR3 pos)
	{
		this->position = pos;
	}
	Vertex(float x, float y)
	{
		this->position = D3DXVECTOR3(x, y, 0);
	}
	static D3D11_INPUT_ELEMENT_DESC desc[];
	static UINT count;
};

//vertex - position, color
struct VertexPC
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
	VertexPC()
	{
		position = D3DXVECTOR3(0, 0, 0);
		//RGBA
		color = D3DXCOLOR(0, 0, 0, 1);
	}
	VertexPC(D3DXVECTOR3 position, D3DXCOLOR color)
	{
		this->position = position;
		this->color = color;
	}
	static D3D11_INPUT_ELEMENT_DESC desc[];
	static UINT count;
};

//Texture Mapping
struct VertexPT
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texCoord;

	VertexPT()
	{
		position = { 0,0,0 };
		texCoord = { 0,0 };
	}
	VertexPT(D3DXVECTOR3 position, D3DXVECTOR2 texCoord)
	{
		this->position = position;
		this->texCoord = texCoord;
	}
	VertexPT(float x, float y, float z, float u, float v)
	{
		this->position = { x, y, z };
		this->texCoord = { u,v };
	}
	static D3D11_INPUT_ELEMENT_DESC desc[];
	static UINT count;
};

inline void CreateVertexBuffer(ID3D11Buffer** buffer, void* data, UINT size)
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = size;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = data;

	DEVICE()->CreateBuffer(&bufferDesc, &Data, buffer);
}