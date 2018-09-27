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
	
	rect1 = new Rect;
	rect1->Init(D3DXCOLOR(1, 0, 0, 1), vsBlob);
	rect1->SetRectCenterPosition(0, 0, 0.1f, 0.1f);
	position = D3DXVECTOR3(0, 0, 0);

	rect2 = new Rect;
	rect2->Init(D3DXCOLOR(0, 1, 0, 1), vsBlob);
	rect2->SetRectCenterPosition(0.5f, 0.5f, 0.1f, 0.1f);

}

void MainGame::Release()
{
	SAFE_RELEASE(vs);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(psBlob);
	
}

void MainGame::Update()
{


	if (GetAsyncKeyState('W') & 0x8000)
	{
		position.y += 0.001f;
		rect1->SetRectCenterPosition(position.x,
			position.y, 0.1f, 0.1f);
		if (Intersect::IsConstainRect(NULL, rect1, rect2))
		{
			rect2->SetRectCenterPosition(
				position.x,
				position.y + 0.11f,
				0.1f, 0.1f);
		}
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		position.y += -0.001f;
		rect1->SetRectCenterPosition(position.x,
			position.y, 0.1f, 0.1f);
		if (Intersect::IsConstainRect(NULL, rect1, rect2))
		{
			rect2->SetRectCenterPosition(
				position.x,
				position.y - 0.11f,
				0.1f, 0.1f);
		}
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		position.x += -0.001f;
		rect1->SetRectCenterPosition(position.x,
			position.y, 0.1f, 0.1f);
		if (Intersect::IsConstainRect(NULL, rect1, rect2))
		{
			rect2->SetRectCenterPosition(
				position.x-0.11f,
				position.y ,
				0.1f, 0.1f);
		}
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		position.x += 0.001f;
		rect1->SetRectCenterPosition(position.x,
			position.y, 0.1f, 0.1f);
		if (Intersect::IsConstainRect(NULL, rect1, rect2))
		{
			rect2->SetRectCenterPosition(
				position.x + 0.11f,
				position.y,
				0.1f, 0.1f);
		}
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{

	}
}

void MainGame::Render()
{
	rect1->Render();
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
	D3DXMatrixOrthoOffCenterLH
	(
		&WVPBufferData.Projection,
		0, desc.Width, desc.Height, 0,
		0.0f, 1.0f
	);
}

void MainGame::SetWVPData(D3DXMATRIX World)
{
}
