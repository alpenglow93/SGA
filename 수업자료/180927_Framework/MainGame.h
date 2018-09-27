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
	Rect* rect2; //���� rect;
private:
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	D3DXVECTOR3 position[3];
	D3DXMATRIX matWorld[3];
	Index index;
public:
	MainGame();
	~MainGame();

	void Init(); //�ʱ�ȭ
	void Release(); // ���� 
	void Update(); //Ű�Է� , ���, ���콺 
	void Render(); //��� 
	void UpdatePosition();

private:
	void CreateWVPBuffer();
	void SetWVPData(D3DXMATRIX World);
private:
	ID3D11Buffer * WVPBuffer;
	WVPBufferDesc WVPBufferData;
};

