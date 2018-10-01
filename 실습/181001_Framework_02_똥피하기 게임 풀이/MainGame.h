#pragma once
#include "Rect.h"
//똥피하기 게임 풀이

#define BEADMAX 20	//떨어질 rect의 갯수

struct tagBead
{
	D3DXMATRIX matWorld;	//물체의 위치, 크기, 회전
	D3DXVECTOR3 position;	//이동하는 좌표
};

//enum Index
//{
//	Index_first,
//	Index_second
//};

class MainGame
{
private:
	Rect* player;
	Rect* beadRect;	//떨어질 사각형 도형

	D3DXVECTOR3 playerPos;	//플레이어 위치
	D3DXMATRIX matWorld;
	tagBead beadInfo[20];	//떨어질 rect의 정보

public:
	MainGame();
	~MainGame();

	void Init();	//초기화
	void Release();	//삭제
	void Update();	//키입력, 계산, 마우스
	void Render();	//출력

private:
	void CreateWVPBuffer();
	void CreateShader();
	void SetWVPData(D3DXMATRIX World);
private:
	struct WVPBufferDesc
	{
		D3DXMATRIX World;
		D3DXMATRIX View;
		D3DXMATRIX Projection;

	};
	ID3D11Buffer * WVPBuffer;
	WVPBufferDesc WVPBufferData;
private:
	ID3D11VertexShader * vs;
	ID3D11PixelShader* ps;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;
};

