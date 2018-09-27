#pragma once
#include "Rect.h"
struct WVPBufferDesc
{
	D3DXMATRIX World;
	D3DXMATRIX View;
	D3DXMATRIX Projection;
};

class MainGame
{
private:
	Rect* rect1;
	Rect* rect2;
private:
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	D3DXVECTOR3 position;

public:
	MainGame();
	~MainGame();

	void Init(); //초기화
	void Release(); // 삭제 
	void Update(); //키입력 , 계산, 마우스 
	void Render(); //출력 
	void UpdatePosition();

private:
	void CreateWVPBuffer();
	void SetWVPData(D3DXMATRIX World);
private:
	ID3D11Buffer * WVPBuffer;
	WVPBufferDesc WVPBufferData;
};

