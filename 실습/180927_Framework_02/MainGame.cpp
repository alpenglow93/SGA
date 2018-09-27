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

		////VertexBuffer Setting
		//////vertexCount = 2;
		//////Vertex* vertices = new Vertex[vertexCount];
		//////vertices[0].position = D3DXVECTOR3(0.0f, -0.2f, 0.0f);
		//////vertices[1].position = D3DXVECTOR3(1.0f, -0.2f, 0.0f);
		//vertexCount = 37;
		//VertexPC* vertices = new VertexPC[vertexCount];

		//float PI = 3.1415928;

		//float intervalAngle = (2 * PI) / 36;
		//for (int i = 0; i < 37; i++)
		//{
		//	vertices[i] = VertexPC
		//	(
		//		D3DXVECTOR3(
		//			cos(i * intervalAngle) * 0.1f,
		//			sin(i * intervalAngle) * 0.1f,
		//			0),
		//		D3DXCOLOR(1, 0, 0, 1)
		//	);
		//}

		////Create VertexBuffer
		//{
		//	D3D11_BUFFER_DESC bufferDesc = { 0 };
		//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//	bufferDesc.ByteWidth = sizeof(VertexPC) * vertexCount;
		//	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//	D3D11_SUBRESOURCE_DATA data = { 0 };
		//	data.pSysMem = vertices;

		//	HRESULT hr = DEVICE()->CreateBuffer(
		//		&bufferDesc, &data, &vertexBuffer
		//	);
		//	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
		//	SAFE_DELETE_ARRAY(vertices);
		//}
		////Create RectBuffer
		//{
		//	RectCount = 6;
		//	RectVertex = new VertexPC[RectCount];
		//	RectVertex[0] =
		//		VertexPC(D3DXVECTOR3(-0.5f, -0.1f, 0.0f),
		//			D3DXCOLOR(1, 1, 0, 1));
		//	RectVertex[1] =
		//		VertexPC(D3DXVECTOR3(-0.5f, 0.1f, 0.0f),
		//			D3DXCOLOR(1, 0, 0, 1));
		//	RectVertex[2] =
		//		VertexPC(D3DXVECTOR3(-0.4f, 0.1f, 0.0f),
		//			D3DXCOLOR(0, 1, 0, 1));
		//	RectVertex[3] =
		//		VertexPC(D3DXVECTOR3(-0.5f, -0.1f, 0.0f),
		//			D3DXCOLOR(1, 1, 0, 1));
		//	RectVertex[4] =
		//		VertexPC(D3DXVECTOR3(-0.4f, 0.1f, 0.0f),
		//			D3DXCOLOR(0, 1, 0, 1));
		//	RectVertex[5] =
		//		VertexPC(D3DXVECTOR3(-0.4f, -0.1f, 0.0f),
		//			D3DXCOLOR(0, 0, 1, 1));

		//	D3D11_BUFFER_DESC bufferDesc = { 0 };
		//	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		//	bufferDesc.ByteWidth = sizeof(VertexPC) * RectCount;
		//	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//	D3D11_SUBRESOURCE_DATA data = { 0 };
		//	data.pSysMem = RectVertex;

		//	HRESULT hr = DEVICE()->CreateBuffer(
		//		&bufferDesc, &data, &RectBuffer
		//	);
		//	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
		//}
		////Create layout
		//{
		//	//D3D11_INPUT_ELEMENT_DESC layoutDesc =
		//	//{
		//	//	"POSITION",		//중요!! 시멘틱: 변수를 어떤 걸로 쓰냐?
		//	//	0,
		//	//	DXGI_FORMAT_R32G32B32_FLOAT,	//집어넣은 데이터 갯수 및 크기
		//	//	0,
		//	//	0,								//0, 데이터의 시작 바이트 단위
		//	//	D3D11_INPUT_PER_VERTEX_DATA,	//vertexBuffer에서 사용하겠다
		//	//	0
		//	//};
		//	//HRESULT hr = DEVICE()->CreateInputLayout(
		//	//	&layoutDesc, 1,
		//	//	vsBlob->GetBufferPointer(),
		//	//	vsBlob->GetBufferSize(),
		//	//	&vertexLayout
		//	//);
		//	//assert(SUCCEEDED(hr) && "Not Create layout");
		//	HRESULT hr = DEVICE()->CreateInputLayout(
		//		VertexPC::desc, VertexPC::count,
		//		vsBlob->GetBufferPointer(),
		//		vsBlob->GetBufferSize(),
		//		&vertexLayout
		//	);
		//	assert(SUCCEEDED(hr) && "Not Create layout");
		//}
		//position = D3DXVECTOR3(0, 0, 0);
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
	//SAFE_RELEASE(vertexLayout);
	//SAFE_RELEASE(vertexBuffer);
	//SAFE_RELEASE(RectBuffer);
	//SAFE_DELETE_ARRAY(RectVertex);
	SAFE_RELEASE(WVPBuffer);
}

void MainGame::Update()
{
	//position = D3DXVECTOR3(0, 0, 0);

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
	else if (GetAsyncKeyState('A') & 0x8000)
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
		//큰 사각형 중심 - 반지름 >= 작은사각형 중심 - 반지름
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
	//D3DXMatrixTranslation() 이동하는 함수
	//out 행렬, x이동, y이동
	for (int i = 0; i < 3; i++)
	{
		D3DXMatrixTranslation(&matWorld[i], position[i].x, position[i].y, position[i].z);
	}
}

void MainGame::Render()
{
	//UINT stride = sizeof(VertexPC);
	//UINT offset = 0;

	//DEVICECONTEXT()->IASetInputLayout(vertexLayout);
	//DEVICECONTEXT()->IASetPrimitiveTopology(
	//	D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	//);

	//DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	////DEVICECONTEXT()->IASetInputLayout(vertexLayout);
	//DEVICECONTEXT()->Draw(vertexCount, 0);

	//DEVICECONTEXT()->IASetPrimitiveTopology(
	//	D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	//);
	//DEVICECONTEXT()->IASetVertexBuffers(0, 1, &RectBuffer,
	//	&stride, &offset);
	//DEVICECONTEXT()->Draw(RectCount, 0);
	
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
	//D3D11_MAPPED_SUBRESOURCE resource;
	//ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	//for (int i = 0; i < RectCount; i++)
	//	RectVertex[i].position += position;

	//HRESULT hr = DEVICECONTEXT()->Map(RectBuffer, 0,
	//	D3D11_MAP_WRITE_DISCARD, 0, &resource);
	//assert(SUCCEEDED(hr) && "Not RectBuffer Mapping");
	//memcpy(resource.pData, RectVertex, sizeof(VertexPC) * RectCount);

	//DEVICECONTEXT()->Unmap(RectBuffer, 0);
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
