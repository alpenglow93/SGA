#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"

#define BULLETMAX 20

//탱크
typedef struct tagTank
{
	Rect* body;		//몸통
	Circle* head;	//머리
	Rect* cannon;	//포신

	//hp 관련
	int maxHp, curHp;
	Rect* back;		//후면
	Rect* front;	//정면

	//딜레이
	//unsigned int currTime - lastTime = 시간
	UINT lastTime;
	UINT currTime;
	UINT fireTime;	//딜레이 시간

	float angle;
	D3DXVECTOR3 fire;
	//D3DXVECTOR3 position;

	bool reverse;
}Tank;

typedef struct tagBullet
{
	Circle* circle;
	float angle;
	bool fire;
	D3DXVECTOR3 position;

	float tempY;
}Bullet;

class MainGame
{
private:
	Tank tank[2];
	Bullet bullet[BULLETMAX];	//총알은 공유해서 사용

	Rect* wall;	//가운데 벽
	
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

