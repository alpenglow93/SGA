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
	player->SetRectCenterPosition(0, 0, 100.0f, 100.0f);
	playerPos = D3DXVECTOR3(desc.Width / 2, desc.Height / 2, 0.0f);
	D3DXMatrixTranslation(&matWorld, playerPos.x, playerPos.y, 0);

	beadRect = new Rect;
	beadRect->Init(vsBlob);
	beadRect->SetRectCenterPosition(0.0f, 0.0f, 100.0f, 100.0f);
	for (int i = 0; i < 20; i++)
	{
		beadInfo[i].position = D3DXVECTOR3
		(
			200.0f + 150.0f * (i % 4),
			100.0f + 125.0f * (i / 4),
			0
		);
		D3DXMatrixTranslation(&beadInfo[i].matWorld,
			beadInfo[i].position.x, beadInfo[i].position.y, 0);
		beadInfo[i].color = D3DXCOLOR(0, 0, 1, 1);
		beadInfo[i].bClick = false;
	}
	target = rand() % 20;
	beadInfo[target].color = D3DXCOLOR(1, 0, 0, 1);
}

void MainGame::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(beadRect);
}

void MainGame::Update()
{
	if (Input->GetKeyDown(VK_LBUTTON))
	{
		if (Intersect::IsConstainsPoint(player, matWorld, vMouse))
		{
			//충돌처리
			bClick = true;
		}
	}
	if (Input->GetKey(VK_LBUTTON))
	{
		if (bClick == true)
		{
			playerPos = vMouse;
		}
	}
	if (Input->GetKeyUp(VK_LBUTTON))
	{
		bClick = false;
	}
	D3DXMatrixTranslation(&matWorld, playerPos.x, playerPos.y, 0);
}

void MainGame::Render()
{
	for (int i = 0; i < BEADMAX; i++)
	{
		this->SetWVPData(beadInfo[i].matWorld);
		beadRect->SetColor(D3DXCOLOR(0, 0, 0, 1));
		beadRect->Render();
	}
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
