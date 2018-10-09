#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"

#define BULLETMAX 1000

typedef struct tagBullet
{
	Circle* circle;				//도형
	D3DXVECTOR3 startPosition;	//시작위치
	D3DXVECTOR3 position;		//움직이는 위치
	//float angle;
	D3DXVECTOR3 velocity;	//방향

	bool bFire;					//발사 여부

}Bullet, *LPBullet;

class MainGame
{
private:
	Circle* body;	//몸통
	Rect* cannon;	//포신

	Bullet bullet[BULLETMAX];	//총알

	float angle;			//각도
	D3DXVECTOR3 fireCoord;	//발사위치

	D3DXMATRIX matParent;	//포신의 위치를 이동
	D3DXMATRIX matWorld;	//포신 회전 용도

public:
	MainGame();
	~MainGame();

	void Init();	//초기화
	void Release();	//삭제
	void Update();	//키입력, 계산, 마우스
	void Render();	//출력
	void CollisionWindow();
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

