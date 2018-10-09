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
	body = new Circle;
	body->Init(vsBlob, 50.0f);
	body->SetPosition(desc.Width / 2.0f, 0.0f);

	cannon = new Rect;
	cannon->Init(vsBlob);
	cannon->SetRectCenterPosition(50, 0, 100, 20);

	//D3DXToRadian() -> degree 를 radian 으로 변환
	//angle = D3DXToRadian(0.0f);
	angle = 90.0f;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matParent);

	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i].circle = NULL;	//발사 전 도형은 없다
		bullet[i].bFire = false;
	}

}

void MainGame::Release()
{
	SAFE_DELETE(body);
	SAFE_DELETE(cannon);
	for (int i = 0; i < BULLETMAX; i++)
		SAFE_DELETE(bullet[i].circle);
}

void MainGame::Update()
{
	//if (Input->GetKey(VK_LEFT) && angle < D3DXToRadian(170.0f))
	//	angle += D3DXToRadian(3.0f);
	//if (Input->GetKey(VK_RIGHT) && angle > D3DXToRadian(10.0f))
	//	angle -= D3DXToRadian(1.0f);	

	if (Input->GetKey(VK_LEFT) && angle < 170.0f)
		angle += 1.0f;
	if (Input->GetKey(VK_RIGHT) && angle > 10.0f)
		angle -= 1.0f;

	////Rect 위치 이동
	//D3DXMATRIX matTrans;
	//D3DXMatrixTranslation(&matTrans, desc.Width / 2, 0.0f, 0.0f);
	////Rect 회전	//회전 행렬 계산
	//D3DXMATRIX matRot;	//회전 형렬 선언
	//D3DXMatrixRotationZ(&matRot, angle);	//행렬 계산
	//matWorld = matRot * matTrans;	//행렬을 이용하여 world 계산

	cannon->SetPosition(desc.Width / 2, 0.0f);
	cannon->SetAngle(angle);

	//fireCoord;
	D3DXMATRIX matFireTrans;	//rect 에서 떨어진 위치
	D3DXMatrixIdentity(&matFireTrans);
	matFireTrans._41 = 120.0f;

	//matFireTrans *= matWorld;
	matFireTrans *= cannon->GetWorld();////////////////////////////////////////////////////////////////////////////////////
	fireCoord = { 0, 0, 0 };
	D3DXVec3TransformCoord(&fireCoord, &fireCoord, &matFireTrans);

	if (Input->GetKeyDown(VK_SPACE))
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (bullet[i].bFire) continue;
			if (bullet[i].circle == NULL)
			{
				bullet[i].circle = new Circle;
				bullet[i].circle->Init(vsBlob, 25.0f);
			}
			bullet[i].position = bullet[i].startPosition = fireCoord;
			bullet[i].circle->SetPosition(bullet[i].position);
			//bullet[i].angle = angle;
			//bullet[i].angle = D3DXToRadian(angle);
			D3DXVECTOR3 vec = { 1, 0, 0 };
			D3DXVec3TransformNormal(&vec, &vec, &cannon->GetWorld());
			D3DXVec3Normalize(&vec, &vec);	//벡터의 길이를 1로

			bullet[i].velocity = vec;
			bullet[i].bFire = true;
			break;
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i].bFire) continue;	//* (속도 )
		//bullet[i].position.x += cos(bullet[i].angle) * 1.0f;
		//bullet[i].position.y += sin(bullet[i].angle) * 1.0f;
		bullet[i].position += bullet[i].velocity * 1.0f;
		//D3DXVECTOR3 distance = bullet[i].position - bullet[i].startPosition;
		//if (D3DXVec3Length(&distance) > 5000.0f) bullet[i].bFire = false;	//300.0f -> 총알 사거리
		bullet[i].circle->SetPosition(bullet[i].position);
	}

	////총알끼리 충돌
	//for (int i = 0; i < BULLETMAX; i++)
	//{
	//	if (!bullet[i].bFire) continue;
	//	for (int j = i + 1; j < BULLETMAX; j++)
	//	{
	//		if (!bullet[j].bFire) continue;
	//		if (Intersect::IsConstainsCircle(bullet[i].circle, bullet[j].circle))
	//		{
	//			//충돌 각도
	//			//A - B 각도 계산 -> B, B - A 각도 계산 -> A
	//			//bullet[i].angle = Intersect::GetAngle(bullet[j].circle, bullet[i].circle);
	//			//bullet[j].angle = Intersect::GetAngle(bullet[i].circle, bullet[j].circle);
	//			D3DXVECTOR3 temp = bullet[i].velocity +
	//				bullet[j].velocity;
	//			D3DXVec3Normalize(&temp, &temp);
	//			bullet[i].velocity = temp;
	//			bullet[j].velocity = -temp;
	//			//막 쓴 코드라 이상함

	//		}
	//	}
	//}
	CollisionWindow();
}

void MainGame::Render()
{
	//this->SetWVPData(matWorld);
	this->SetWVPData(cannon->GetWorld());

	cannon->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	cannon->Render();

	this->SetWVPData(body->GetMatrix());
	body->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	body->Render();

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i].bFire) continue;
		bullet[i].circle->SetColor(D3DXCOLOR(0, 0, 1, 1));
		bullet[i].circle->Render();
		this->SetWVPData(bullet[i].circle->GetMatrix());
	}
}

//윈도우와 부딪혀 튕겨져나오는 코드
void MainGame::CollisionWindow()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i].bFire) continue;
		//1. 위, 아래	//25.0f 구체의 반지름
		if (bullet[i].position.y + 25.0f > desc.Height ||	//구체의 윗방향
			bullet[i].position.y - 25.0f < 0.0f	//구체의 아래 방향
			)
		{
			//bullet[i].angle = -bullet[i].angle;
			//2 * D3DX_PI - bullet[i].angle; = -bullet[i].angle;
			bullet[i].velocity.y = -bullet[i].velocity.y;
		}
		//2. 좌, 우
		if (bullet[i].position.x - 25.0f < 0.0f ||	//왼쪽
			bullet[i].position.x + 25.0f > desc.Width
			)
		{
			bullet[i].velocity.x = -bullet[i].velocity.x;
			//bullet[i].angle = D3DX_PI - bullet[i].angle;
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
