#pragma once
#include "Rect.h"
//�����ϱ� ���� Ǯ��

#define BEADMAX 20	//������ rect�� ����

struct tagBead
{
	D3DXMATRIX matWorld;	//��ü�� ��ġ, ũ��, ȸ��
	D3DXVECTOR3 position;	//�̵��ϴ� ��ǥ
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
	Rect* beadRect;	//������ �簢�� ����

	D3DXVECTOR3 playerPos;	//�÷��̾� ��ġ
	D3DXMATRIX matWorld;
	tagBead beadInfo[20];	//������ rect�� ����

public:
	MainGame();
	~MainGame();

	void Init();	//�ʱ�ȭ
	void Release();	//����
	void Update();	//Ű�Է�, ���, ���콺
	void Render();	//���

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

