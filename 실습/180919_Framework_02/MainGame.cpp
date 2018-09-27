#include "stdafx.h"
#include "MainGame.h"


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

		//VertexBuffer Setting
		vertexCount = 2;
		Vertex* vertices = new Vertex[vertexCount];
		vertices[0].position = D3DXVECTOR3(0.0f, -0.2f, 0.0f);
		vertices[1].position = D3DXVECTOR3(1.0f, -0.2f, 0.0f);

		//Create VertexBuffer
		{
			D3D11_BUFFER_DESC bufferDesc = { 0 };
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.ByteWidth = sizeof(Vertex)
				* vertexCount;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data = { 0 };
			data.pSysMem = vertices;

			HRESULT hr = DEVICE()->CreateBuffer(
				&bufferDesc, &data, &vertexBuffer
			);
			assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
			SAFE_DELETE_ARRAY(vertices);
		}
		//Create layout
		{
			D3D11_INPUT_ELEMENT_DESC layoutDesc =
			{
				"POSITION",		//중요!! 시멘틱: 변수를 어떤 걸로 쓰냐?
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,	//집어넣은 데이터 갯수 및 크기
				0,
				0,								//0, 데이터의 시작 바이트 단위
				D3D11_INPUT_PER_VERTEX_DATA,	//vertexBuffer에서 사용하겠다
				0
			};
			HRESULT hr = DEVICE()->CreateInputLayout(
				&layoutDesc, 1,
				vsBlob->GetBufferPointer(),
				vsBlob->GetBufferSize(),
				&vertexLayout
			);
			assert(SUCCEEDED(hr) && "Not Create layout");
		}
	}
}

void MainGame::Release()
{
	SAFE_RELEASE(vs);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(vertexLayout);
	SAFE_RELEASE(vertexBuffer);
}

void MainGame::Update()
{
}

void MainGame::Render()
{
	UINT strde = sizeof(Vertex);
	UINT offset = 0;

	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &strde, &offset);
	DEVICECONTEXT()->IASetInputLayout(vertexLayout);

	DEVICECONTEXT()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	);
	DEVICECONTEXT()->Draw(vertexCount, 0);
}
