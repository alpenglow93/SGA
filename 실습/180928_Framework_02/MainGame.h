#pragma once
#include "Rect.h"
struct WVPBufferDesc
{
	D3DXMATRIX World;
	D3DXMATRIX View;
	D3DXMATRIX Projection;

};

enum Index
{
	Index_first,
	Index_second
};

class MainGame
{
private:
	Rect* rect1;
	Rect *rect2;	//���� rect
private:
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	//ID3D11Buffer* vertexBuffer;
	//ID3D11InputLayout* vertexLayout;
	//D3D11_INPUT_ELEMENT_DESC layoutDesc;


	//struct Vertex
	//{
	//	D3DXVECTOR3 position;
	//};

	//UINT vertexCount;

	//ID3D11Buffer* RectBuffer;
	//UINT RectCount;
	//UINT vertexCount;

	D3DXVECTOR3 position[3];
	//VertexPC* RectVertex;

	D3DXMATRIX matWorld[3];
	Index index;

	D3DXCOLOR color[2];

public:
	MainGame();
	~MainGame();

	void Init();	//�ʱ�ȭ
	void Release();	//����
	void Update();	//Ű�Է�, ���, ���콺
	void Render();	//���
	void UpdatePosition();

private:
	void CreateWVPBuffer();
	void SetWVPData(D3DXMATRIX World);
private:
	ID3D11Buffer * WVPBuffer;
	WVPBufferDesc WVPBufferData;
};

