#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"

#define BULLETMAX 1000

typedef struct tagBullet
{
	Circle* circle;				//����
	D3DXVECTOR3 startPosition;	//������ġ
	D3DXVECTOR3 position;		//�����̴� ��ġ
	//float angle;
	D3DXVECTOR3 velocity;	//����

	bool bFire;					//�߻� ����

}Bullet, *LPBullet;

class MainGame
{
private:
	Circle* body;	//����
	Rect* cannon;	//����

	Bullet bullet[BULLETMAX];	//�Ѿ�

	float angle;			//����
	D3DXVECTOR3 fireCoord;	//�߻���ġ

	D3DXMATRIX matParent;	//������ ��ġ�� �̵�
	D3DXMATRIX matWorld;	//���� ȸ�� �뵵

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

