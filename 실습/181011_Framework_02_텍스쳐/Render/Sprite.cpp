#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}

Sprite::Sprite(wstring file)
{
	//�ؽ��� ���� �ε�
	wstring filePath = L"./_Textures/" + file;
	HRESULT hr;
	D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE(), filePath.c_str(), NULL, NULL, &srv, &hr
	);
	assert(SUCCEEDED(hr) && "Not Create Texture");

	//���̴� �ʱ�ȭ
	shader = new Shader(L"Sprite.hlsl");
	shader->CreateInputLayout(VertexPT::desc, VertexPT::count);

	//vertices ����
	vertices = new VertexPT[VertexCount];
	vertices[0].position = { -0.5f, -0.5f, 0.0f };	//���ʾƷ�
	vertices[1].position = { -0.5f, 0.5f, 0.0f };	//������
	vertices[2].position = { 0.5f, 0.5f, 0.0f };	//��������

	vertices[3].position = vertices[0].position;
	vertices[4].position = vertices[2].position;
	vertices[5].position = { 0.5f, -0.5f, 0.0f };	//����

	//texCoord ���� 0 ~ 1
	vertices[0].texCoord = { 0.0f, 1.0f };
	vertices[1].texCoord = { 0.0f, 0.0f };
	vertices[2].texCoord = { 1.0f, 0.0f };

	vertices[3].texCoord = vertices[0].texCoord;
	vertices[4].texCoord = vertices[2].texCoord;
	vertices[5].texCoord = { 1.0f, 1.0f };

	//CreateVertexBuffer
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;	//default ����
	bufferDesc.ByteWidth = sizeof(VertexPT) * VertexCount;
	//CpuAdress ����
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };	//�߰�
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices;	//�߰�

	hr = DEVICE()->CreateBuffer(
		&bufferDesc,
		&data, &vertexBuffer);	//NULL->&data ����
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
}


Sprite::~Sprite()
{
	SAFE_DELETE(shader);
	SAFE_DELETE_ARRAY(vertices);

	SAFE_RELEASE(vertexBuffer);
}

void Sprite::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Sprite::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void Sprite::Update()
{
	D3DXMATRIX S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T,
		position.x + scale.x * 0.5f,
		position.y + scale.y * 0.5f, 1.0f);
	
	shader->SetWVPData(S * T);
}

void Sprite::Render()
{
	UINT stride = sizeof(VertexPT);
	UINT offset = 0;

	shader->SetShader();

	DEVICECONTEXT()->PSSetShaderResources(0, 1, &srv);
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DEVICECONTEXT()->Draw(VertexCount, 0);
}
