#include "stdafx.h"
#include "MainGame.h"
#include "Intersect.h"


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

	////CreateWVP
	//{
	//	this->CreateWVPBuffer();
	//}

	player = new Rect;
	player->Init(vsBlob);
	player->SetRectCenterPosition(0, 0, 50.0f, 50.0f);

	beadRect = new Rect;
	beadRect->Init(vsBlob);
	beadRect->SetRectCenterPosition(0, 0, 50.0f, 50.0f);

	playerPos = D3DXVECTOR3(desc.Width / 2, 50, 0);
	for (int i = 0; i < BEADMAX; i++)
	{
		beadInfo[i].position = D3DXVECTOR3
		(
			25.0f + (desc.Width / BEADMAX) * i,
			desc.Height + (rand() % 50) * 10,
			0
		);
	}
}

void MainGame::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(beadRect);
}

void MainGame::Update()
{
	if (Input->GetKey('A'))
	{
		playerPos.x -= 1.0f;
	}
	if (Input->GetKey('D'))
	{
		playerPos.x += 1.0f;
	}
	D3DXMatrixTranslation(&matWorld, playerPos.x, playerPos.y, 0);
	for (int i = 0; i < BEADMAX; i++)
	{
		beadInfo[i].position.y -= 0.5f;	//떨어지는 속도
		D3DXMatrixTranslation(&beadInfo[i].matWorld,
			beadInfo[i].position.x, beadInfo[i].position.y, 0);
		if (beadInfo[i].position.y < -25.0f)
		{
			beadInfo[i].position.y = desc.Height + (rand() % 50) * 10;
		}
		D3DXMatrixTranslation(&beadInfo[i].matWorld,
			beadInfo[i].position.x, beadInfo[i].position.y, 0);
	}
	for (int i = 0; i < BEADMAX; i++)
	{
		if (Intersect::IsConstainRect(player, matWorld, beadRect, beadInfo[i].matWorld))
		{
			//죽음 처리 (창 종료, 점수출력, 게임 다시시작, etc)
			//PostQuitMessage(0);	//창 종료 함수
			//this->Init();			//다시 시작
			MessageBox(NULL, L"YOU DIE", L"GAME OVER", MB_OK);
		}
	}
}

void MainGame::Render()
{
	for (int i = 0; i < BEADMAX; i++)
	{
		this->SetWVPData(beadInfo[i].matWorld);

		float r = (rand() % 1001) / 1000.0f;
		float g = (rand() % 1001) / 1000.0f;
		float b = (rand() % 1001) / 1000.0f;


		beadRect->SetColor(D3DXCOLOR(r, g, b, 1));
		beadRect->Render();
	}
	this->SetWVPData(matWorld);
	player->SetColor(D3DXCOLOR(0, 0, 1, 1));
	player->Render();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//똥피하기 게임 풀이에서는 이 아래는 신경 안 씀
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
