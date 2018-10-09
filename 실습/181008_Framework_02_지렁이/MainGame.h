#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"

#define BULLETMAX 20

typedef struct tagBullet
{
	Circle* circle;				//도형
	D3DXVECTOR3 position;		//움직이는 위치
	float angle;
	float radius;
}Bullet, *LPBullet;

class MainGame
{
private:
	//Bullet bullet[BULLETMAX];	//총알
	vector<Bullet> bullet;
	Circle* item;

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

