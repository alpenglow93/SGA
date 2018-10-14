#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"

#define BULLETMAX 20

//��ũ
typedef struct tagTank
{
	Rect* body;		//����
	Circle* head;	//�Ӹ�
	Rect* cannon;	//����

	//hp ����
	int maxHp, curHp;
	Rect* back;		//�ĸ�
	Rect* front;	//����

	//������
	//unsigned int currTime - lastTime = �ð�
	UINT lastTime;
	UINT currTime;
	UINT fireTime;	//������ �ð�

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
	Bullet bullet[BULLETMAX];	//�Ѿ��� �����ؼ� ���

	Rect* wall;	//��� ��
	
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

