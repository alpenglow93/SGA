#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"

#define BULLETMAX 20

typedef struct tagBullet
{
	Circle* circle;				//����
	D3DXVECTOR3 position;		//�����̴� ��ġ
	float angle;
	float radius;
}Bullet, *LPBullet;

class MainGame
{
private:
	//Bullet bullet[BULLETMAX];	//�Ѿ�
	vector<Bullet> bullet;
	Circle* item;

public:
	MainGame();
	~MainGame();

	void Init();	//�ʱ�ȭ
	void Release();	//����
	void Update();	//Ű�Է�, ���, ���콺
	void Render();	//���
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

