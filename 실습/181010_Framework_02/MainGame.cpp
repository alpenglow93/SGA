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
	for (int i = 0; i < 2; i++)
	{
		tank[i].body = new Rect;
		tank[i].body->Init(vsBlob);
		tank[i].body->SetRectCenterPosition(0, 0, 100, 50);

		tank[i].head = new Circle;
		tank[i].head->Init(vsBlob, 25.0f);

		tank[i].cannon = new Rect;
		tank[i].cannon->Init(vsBlob);
		tank[i].cannon->SetRectCenterPosition(25, 0, 50, 10);

		//hp 관련
		tank[i].maxHp = tank[i].curHp = 200;

		tank[i].back = new Rect;
		tank[i].back->Init(vsBlob);
		tank[i].back->SetRectCenterPosition(200, 0, 400, 30);


		tank[i].front = new Rect;
		tank[i].front->Init(vsBlob);
		tank[i].front->SetRectCenterPosition(195, 0, 390, 24);

		tank[i].angle = 90.0f;
		tank[i].fire = D3DXVECTOR3(55, 0, 0);
		tank[i].reverse = false;

		//시간	1. GetTickCount	//부팅시부터 현재까지의 시간을 계산해서 현재시간을 받아옴 (부팅시간 기준)
		//		2. timeGetTime	//윈도우가 시작되어 지금까지 흐른 시간

		tank[i].lastTime = GetTickCount();
		tank[i].fireTime = (5 + rand() % 10) * 100;
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i].circle = new Circle;
		bullet[i].circle->Init(vsBlob, 12.5f);
		bullet[i].fire = false;
	}

	wall = new Rect;
	wall->Init(vsBlob);
	wall->SetRectCenterPosition(0, 0, 20, desc.Height / 2);
}

void MainGame::Release()
{
	for (int i = 0; i < 2; i++)
	{
		SAFE_DELETE(tank[i].body);
		SAFE_DELETE(tank[i].head);
		SAFE_DELETE(tank[i].cannon);

		SAFE_DELETE(tank[i].back);
		SAFE_DELETE(tank[i].front);

	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		SAFE_DELETE(bullet[i].circle);
	}
	SAFE_DELETE(wall);
}

void MainGame::Update()
{
	//탱크 위치 설정
	//왼쪽 탱크
	tank[0].body->SetPosition(50, 25);
	tank[0].head->SetPosition(50, 50);
	tank[0].cannon->SetPosition(50, 50);
	tank[0].cannon->SetAngle(tank[0].angle);

	tank[0].back->SetPosition(10, desc.Height - 15);
	tank[0].front->SetPosition(15, desc.Height - 17);


	if (Input->GetKeyDown(VK_SPACE))
	{
		tank[0].curHp -= 10;
		tank[0].front->SetScale((float)tank[0].curHp / (float)tank[0].maxHp, 1.0f);

	}

	//탱크 1개만 자동 발사
	for (int i = 0; i < 2; i++)
	{
		if (i == 1) break;
		if (tank[i].reverse)
		{
			tank[i].angle += 0.5f;
			if (tank[i].angle > 90.0f) tank[i].reverse = false;
		}
		else
		{
			tank[i].angle -= 0.5f;
			if (tank[i].angle < 0.0f) tank[i].reverse = true;
		}

		tank[i].cannon->SetAngle(tank[i].angle);

		tank[i].fire = { 55, 0, 0 };
		D3DXVec3TransformCoord(&tank[i].fire, &tank[i].fire,
			&tank[i].cannon->GetWorld());

		tank[i].currTime = GetTickCount();
		if (tank[i].currTime - tank[i].lastTime > tank[i].fireTime)
		{
			//발사
			for (int j = 0; j < BULLETMAX; j++)
			{
				if (bullet[j].fire) continue;
				bullet[j].position = tank[i].fire;
				bullet[j].angle = tank[j].angle;
				bullet[j].fire = true;
				bullet[j].tempY = 1.0f;

				tank[i].lastTime = tank[i].currTime;
				tank[i].fireTime = (5 + rand() % 10) * 100;
				break;
			}
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		//포물선으로 움직이는 방법은 두가지가 있음
		//1. angle 값을 증가시켰다가 감소 -> 270
		//2. y값에 중력값 더하기 <<이 방법 씀
		if (!bullet[i].fire) continue;
		bullet[i].position.x += cosf(D3DXToRadian(bullet[i].angle)) * 3.0f;
		bullet[i].position.y += sinf(D3DXToRadian(bullet[i].angle)) * 3.0f * bullet[i].tempY;	//중력값은 원래 9.8이지만 게임 상황에 맞춰서 변경해도 됨
		bullet[i].tempY -= 0.005f;
		bullet[i].circle->SetPosition(bullet[i].position);
		CollisionWindow();	//충돌체크
	}
}

void MainGame::Render()
{
	//탱크 출력
	for (int i = 0; i < 2; i++)
	{
		if (i == 1) break;
		this->SetWVPData(tank[i].cannon->GetWorld());
		tank[i].cannon->SetColor(D3DXCOLOR(0, 1, 0, 1));
		tank[i].cannon->Render();

		this->SetWVPData(tank[i].head->GetMatrix());
		tank[i].head->SetColor(D3DXCOLOR(0, 0, 1, 1));
		tank[i].head->Render();

		this->SetWVPData(tank[i].body->GetWorld());
		tank[i].body->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f));
		tank[i].body->Render();

		this->SetWVPData(tank[i].back->GetWorld());
		tank[i].back->SetColor(D3DXCOLOR(0, 0, 0, 1));
		tank[i].back->Render();

		this->SetWVPData(tank[i].front->GetWorld());
		tank[i].front->SetColor(D3DXCOLOR(1, 0, 0, 1));
		tank[i].front->Render();
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i].fire) continue;
		this->SetWVPData(bullet[i].circle->GetMatrix());
		bullet[i].circle->SetColor(D3DXCOLOR(1, 0, 0, 1));
		bullet[i].circle->Render();
	}
}

void MainGame::CollisionWindow()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i].fire) continue;
		if (
			bullet[i].position.x < -13.f ||
			bullet[i].position.x > desc.Width + 13.0f ||
			bullet[i].position.y < -13.f ||
			bullet[i].position.y > desc.Height + 13.0f
			)
		{
			bullet[i].fire = false;
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

	//View(카메라)
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

		//쉐이더 사용을 위한 등록
		DEVICECONTEXT()->VSSetShader(vs, 0, 0);
		DEVICECONTEXT()->PSSetShader(ps, 0, 0);

	}
}

void MainGame::SetWVPData(D3DXMATRIX World)
{
	//world = 이동, 회전, 크기의 데이터가 들어가 있는 녀석
	WVPBufferData.World = World;
	/*
		Transpose()
		1 2 -> 1 0
		0 0    2 0
	*/
	//D3DXMatrixTranspose(out, in )
	D3DXMatrixTranspose(&WVPBufferData.World, &WVPBufferData.World);

	DEVICECONTEXT()->UpdateSubresource(
		WVPBuffer,	//값을 넣을 버퍼
		0,
		NULL,
		&WVPBufferData,	//넣을 데이터
		0, 0);
	DEVICECONTEXT()->VSSetConstantBuffers(0, 1, &WVPBuffer);
}
