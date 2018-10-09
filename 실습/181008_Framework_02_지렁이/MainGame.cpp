#include "stdafx.h"
#include "MainGame.h"
#include "./Utilities/Intersect.h"


MainGame::MainGame()
{
	this->CreateShader();
	this->CreateWVPBuffer();
}


MainGame::~MainGame()
{
	SAFE_RELEASE(vs);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(WVPBuffer);
}

void MainGame::Init()
{
	//for (int i = 0; i < BULLETMAX; i++)
	//{
	//	bullet[i].circle = new Circle();
	//	bullet[i].circle->Init(vsBlob, 25.0f);
	//	bullet[i].position = { desc.Width / 2, desc.Height / 2, 0.0f };
	//	bullet[i].radius = 25.0f;
	//	bullet[i].angle = D3DXToRadian(90.0f);
	//}
	Bullet temp;
	temp.circle = new Circle();
	temp.circle->Init(vsBlob, 25.0f);
	temp.position = { desc.Width / 2, desc.Height / 2, 0.0f };
	temp.radius = 25.0f;
	temp.angle = D3DXToRadian(90.0f);
	bullet.push_back(temp);

	item = new Circle;
	item->Init(vsBlob, 50.0f);
	item->SetPosition(50 + rand() % (int)(desc.Width - 50),
		50 + rand() % (int)(desc.Height - 50));
}

void MainGame::Release()
{
	for (int i = 0; i < bullet.size(); i++)
		SAFE_DELETE(bullet[i].circle);
	SAFE_DELETE(item);
}

void MainGame::Update()
{
	//�Ӹ� �̵�
	if (Input->GetKey(VK_LEFT))
		bullet[0].angle += D3DXToRadian(1.0f);
	if (Input->GetKey(VK_RIGHT))
		bullet[0].angle -= D3DXToRadian(1.0f);
	CollisionWindow();

	if (Intersect::IsConstainsCircle(bullet[0].circle, item))
	{
		item->SetPosition(
			50 + rand() % (int)(desc.Width - 50),
			50 + rand() % (int)(desc.Height - 50));

		Bullet temp;
		temp.circle = new Circle();
		temp.circle->Init(vsBlob, 25.0f);
		temp.position = { desc.Width / 2, desc.Height / 2, 0.0f };
		temp.radius = 25.0f;
		temp.angle = D3DXToRadian(90.0f);
		bullet.push_back(temp);
	}
}

void MainGame::Render()
{
	item->SetColor(D3DXCOLOR(0, 1, 0, 1));
	this->SetWVPData(item->GetMatrix());
	item->Render();
	for (int i = 0; i < bullet.size(); i++)
	{
		if (i == 0)
		{
			bullet[i].circle->SetColor(D3DXCOLOR(1, 0, 0, 1));
		}
		else
		{
			bullet[i].circle->SetColor(D3DXCOLOR(0, 0, 1, 1));
		}
		this->SetWVPData(bullet[i].circle->GetMatrix());
		bullet[i].circle->Render();
	}
}

//������� �ε��� ƨ���������� �ڵ�
void MainGame::CollisionWindow()
{
	for (int i = 0; i < bullet.size(); i++)
	{
		if (i == 0)	//�Ӹ��϶�
		{
			//�Ӹ� �̵�(������)
			bullet[i].position.x += cos(bullet[i].angle) * 1.0f;
			bullet[i].position.y += sin(bullet[i].angle) * 1.0f;
			bullet[i].circle->SetPosition(bullet[i].position);

			if (bullet[i].position.y + 25.0f > desc.Height ||	//��ü�� ������
				bullet[i].position.y - 25.0f < 0.0f	//��ü�� �Ʒ� ����
				)
			{
				//bullet[i].angle = -bullet[i].angle;
				//2 * D3DX_PI - bullet[i].angle; = -bullet[i].angle;
				bullet[i].angle = -bullet[i].angle;
			}
			//2. ��, ��
			if (bullet[i].position.x - 25.0f < 0.0f ||	//����
				bullet[i].position.x + 25.0f > desc.Width
				)
			{
				bullet[i].angle = D3DX_PI -bullet[i].angle;
				//bullet[i].angle = D3DX_PI - bullet[i].angle;
			}
		}
		else //���� ����
		{
			D3DXVECTOR3 distance = bullet[i].position - bullet[i - 1].position;
			if (D3DXVec3Length(&distance) > bullet[i].radius * 2)
			{
				bullet[i].angle = Intersect::GetAngle(bullet[i].circle, bullet[i - 1].circle);

				//��ġ�� �ٽ� ��ġ
				bullet[i].position.x = bullet[i - 1].position.x - cos(bullet[i].angle) * bullet[i].radius * 2;;
				bullet[i].position.y = bullet[i - 1].position.y - sin(bullet[i].angle) * bullet[i].radius * 2;
				bullet[i].circle->SetPosition(bullet[i].position);
			}
			//������ ������
			bullet[i].position.x += cos(bullet[i].angle) * 1.0f;
			bullet[i].position.y += sin(bullet[i].angle) * 1.0f;
			bullet[i].circle->SetPosition(bullet[i].position);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////
void MainGame::CreateWVPBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(WVPBufferDesc);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = DEVICE()->CreateBuffer(
		&bufferDesc, NULL, &WVPBuffer
	);
	assert(SUCCEEDED(hr) && "Not Create WVPBuffer");

	//View(ī�޶�)
	D3DXVECTOR3 vEye(0, 0, 0);
	D3DXVECTOR3 vLookAt(0, 0, 1);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXMatrixLookAtLH(&WVPBufferData.View, &vEye, &vLookAt, &vUp);

	//Projection
	D3DXMatrixOrthoOffCenterLH
	(
		&WVPBufferData.Projection,
		0, desc.Width, 0, desc.Height,
		0.0f, 1.0f
	);
	D3DXMatrixTranspose(&WVPBufferData.View, &WVPBufferData.View);
	D3DXMatrixTranspose(&WVPBufferData.Projection, &WVPBufferData.Projection);
}

void MainGame::CreateShader()
{
	{
		HRESULT hr;
		hr = D3DX11CompileFromFile(
			L"./Shader/Effect.hlsl", 0, 0, "VS", "vs_5_0",
			0, 0, 0, &vsBlob, 0, 0);
		assert(SUCCEEDED(hr) && "Not Compiling VS");
		hr = D3DX11CompileFromFile(
			L"./Shader/Effect.hlsl", 0, 0, "PS", "ps_5_0",
			0, 0, 0, &psBlob, 0, 0);
		assert(SUCCEEDED(hr) && "Not Compiling PS");

		hr = DEVICE()->CreateVertexShader(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), NULL, &vs
		);
		assert(SUCCEEDED(hr) && "Not Create VS");

		hr = DEVICE()->CreatePixelShader(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(), NULL, &ps
		);
		assert(SUCCEEDED(hr) && "Not Create PS");

		//���̴� ����� ���� ���
		DEVICECONTEXT()->VSSetShader(vs, 0, 0);
		DEVICECONTEXT()->PSSetShader(ps, 0, 0);

	}
}

void MainGame::SetWVPData(D3DXMATRIX World)
{
	//world = �̵�, ȸ��, ũ���� �����Ͱ� �� �ִ� �༮
	WVPBufferData.World = World;
	/*
		Transpose()
		1 2 -> 1 0
		0 0    2 0
	*/
	//D3DXMatrixTranspose(out, in )
	D3DXMatrixTranspose(&WVPBufferData.World, &WVPBufferData.World);

	DEVICECONTEXT()->UpdateSubresource(
		WVPBuffer,	//���� ���� ����
		0,
		NULL,
		&WVPBufferData,	//���� ������
		0, 0);
	DEVICECONTEXT()->VSSetConstantBuffers(0, 1, &WVPBuffer);
}
