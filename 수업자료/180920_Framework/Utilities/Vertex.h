#pragma once

#define VERTEX_XY DXGI_FORMAT_R32G32_FLOAT
#define VERTEX_XYZ DXGI_FORMAT_R32G32B32_FLOAT
#define VERTEX_XYZW DXGI_FORMAT_R32G32B32A32_FLOAT

//vertex - position, color
static struct VertexPC
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