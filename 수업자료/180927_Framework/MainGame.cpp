#include "stdafx.h"
#include "MainGame.h"
#include "Intersect.h"

MainGame::MainGame()
{

}


MainGame::~MainGame()
{
	
}

void MainGame::Init()
{
	//CreateShader
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

	//CreateWVP
	{
		this->CreateWVPBuffer();
	}
	rect1 = new Rect;
	rect1->Init(D3DXCOLOR(1, 0, 0, 1), vsBlob);
	rect1->SetRectCenterPosition(0, 0, 100.0f, 100.0f);

	rect2 = new Rect;
	rect2->Init(D3DXCOLOR(1, 1, 0, 1), vsBlob);
	rect2->SetRectCenterPosition(0, 0, 50.0f, 50.0f);

	position[0] = D3DXVECTOR3(0, 0, 0);
	position[1] = D3DXVECTOR3(0, 0, 0);

	D3DXMatrixIdentity(&matWorld[0]);
	D3DXMatrixIdentity(&matWorld[1]);

	index = Index_first;

	position[0].x = -300.0f;
	position[1].x = 300.0f;
	D3DXMatrixTranslation(&matWorld[0], position[0].x, position[0].y, 0.0f);
	D3DXMatrixTranslation(&matWorld[1], position[1].x, position[1].y, 0.0f);

	position[2] = position[0];
	matWorld[2] = matWorld[0];
}

void MainGame::Release()
{
	SAFE_RELEASE(vs);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(WVPBuffer);
}

void MainGame::Update()
{

	if (GetAsyncKeyState('W') & 0x8000)
	{
		position[index].y += 1.0f;
		if (Intersect::IsConstainRect(
			rect1, matWorld[0], rect1, matWorld[1]
		))
		{
			index = (Index)((index + 1) % 2);
			position[index].y += 2.0f;
		}
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		position[index].y += -1.0f;
		if (Intersect::IsConstainRect(
			rect1, matWorld[0], rect1, matWorld[1]
		))
		{
			index = (Index)((index + 1) % 2);
			position[index].y += -2.0f;

		}
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		position[index].x += -1.0f;
		if (position[index].x + 50 <= position[2].x + 25)
		{
			position[2].x -= 1.0f;
		}
		if (Intersect::IsConstainRect(
			rect1, matWorld[0], rect1, matWorld[1]
		))
		{
			index = (Index)((index + 1) % 2);
			position[index].x += -2.0f;
			position[2] = position[index];

		}
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		position[index].x += 1.0f;
		//큰사각형의 중심 - 반지름  >= 작은 사각형의 중심 - 반지름 
		if (position[index].x - 50 >= position[2].x - 25)
		{
			position[2].x += 1.0f;
		}
		if (Intersect::IsConstainRect(
			rect1, matWorld[0], rect1, matWorld[1]
		))
		{
			index = (Index)((index + 1) % 2);
			position[index].x += 2.0f;
			position[2] = position[index];
		}
	}
	//D3DXMatrixTranslation() 이동 하는 함수
	//out 행렬 ,x 이동 , y 이동 
	for (int i = 0; i < 3; i++)
	{
		D3DXMatrixTranslation(&matWorld[i],
			position[i].x, position[i].y,position[i].z);
	}
}

void MainGame::Render()
{
	//D3DXMatrixIdentity() -> 행렬 초기화
	/*
		{1, 0, 0, 0}
		{0, 1, 0, 0}
		{0, 0, 1, 0}
		{0, 0, 0, 1}
	*/
	for (int i = 0; i < 2; i++)
	{
		this->SetWVPData(matWorld[i]);
		rect1->Render();
	}
	this->SetWVPData(matWorld[2]);
	rect2->Render();
}

void MainGame::UpdatePosition()
{
	
}

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
	D3DXMatrixOrthoLH
	(
		&WVPBufferData.Projection,
		desc.Width, desc.Height,
		0.0f, 1.0f
	);
	D3DXMatrixTranspose(&WVPBufferData.View, &WVPBufferData.View);
	D3DXMatrixTranspose(&WVPBufferData.Projection, &WVPBufferData.Projection);
}

void MainGame::SetWVPData(D3DXMATRIX World)
{
	//world = 이동, 회전, 크기의 데이터가 들어가 있는 녀석 
	WVPBufferData.World = World;
	D3DXMatrixTranspose(&WVPBufferData.World, &WVPBufferData.World);
	
	DEVICECONTEXT()->UpdateSubresource(
		WVPBuffer, //값을 넣을 버퍼 
		0, NULL,
		&WVPBufferData, // 넣을 데이터  
		0, 0);
	DEVICECONTEXT()->VSSetConstantBuffers(0, 1, &WVPBuffer);
}
