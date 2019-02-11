#include "stdafx.h"
#include "Shader.h"


Shader::Shader(wstring file, bool bSubContext)
	:vs(NULL),ps(NULL),cs(NULL),bSubContext(bSubContext),
	vsBlob(NULL), psBlob(NULL), csBlob(NULL),WorldBuffer(NULL)
	,vertexLayout(NULL)
{
	//string.c_str()-> char*

	wstring filePath = file;
	HRESULT hr;
	if (!bSubContext)
	{
		ID3D10Blob* error;
		hr = D3DX11CompileFromFile(
			filePath.c_str(), 0, 0, "VS", "vs_5_0",
			0, 0, 0, &vsBlob, &error, 0);
		if (error != NULL)
		{
			string str = (const char*)error->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "", MB_OK);
		}
		assert(SUCCEEDED(hr) && "Not Compiling VS");

		hr = D3DX11CompileFromFile(
			filePath.c_str(), 0, 0, "PS", "ps_5_0",
			0, 0, 0, &psBlob, &error, 0);
		if (error != NULL)
		{
			string str = (const char*)error->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "", MB_OK);
		}

		SAFE_RELEASE(error);
		assert(SUCCEEDED(hr) && "Not Compiling PS");

		hr = DEVICE()->CreateVertexShader(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), NULL, &this->vs
		);
		assert(SUCCEEDED(hr) && "Not Create VS");

		hr = DEVICE()->CreatePixelShader(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(), NULL, &this->ps
		);
		assert(SUCCEEDED(hr) && "Not Create PS");

		this->CreateBuffer();
	}
	else
	{
		D3DX11CompileFromFile
		(
			file.c_str(), NULL, NULL,
			"CS", "cs_5_0", 0, 0, NULL,
			&csBlob, NULL, &hr
		);

		DEVICE()->CreateComputeShader(
			csBlob->GetBufferPointer(),
			csBlob->GetBufferSize(),
			NULL, &cs
		);
	}
}


Shader::~Shader()
{
	SAFE_RELEASE(vs);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(cs);
	SAFE_RELEASE(csBlob);
	SAFE_RELEASE(WorldBuffer);

	SAFE_RELEASE(vertexLayout); //추가 
}

void Shader::CreateBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(WorldBufferDesc);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = DEVICE()->CreateBuffer(&bufferDesc, NULL, &WorldBuffer);
	assert(SUCCEEDED(hr) && "Not Create WVPBuffer");
}

void Shader::SetWVPData(D3DXMATRIX World)
{
	//world = 이동, 회전, 크기의 데이터가 들어가 있는 녀석 
	WorldBufferData.World = World;
	D3DXMatrixTranspose(&WorldBufferData.World, &WorldBufferData.World);
}

void Shader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC * desc, UINT count)
{
	HRESULT hr = DEVICE()->CreateInputLayout(
		desc,
		count,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&vertexLayout
	);
	assert(SUCCEEDED(hr) && "Not Create LayOut");

}

void Shader::SetShader()
{
	if (!bSubContext)
	{
		assert(vertexLayout != NULL && "Not Initalize VertexLayout");

		DEVICECONTEXT()->VSSetShader(this->vs, 0, 0);
		DEVICECONTEXT()->PSSetShader(this->ps, 0, 0);

		DEVICECONTEXT()->UpdateSubresource(WorldBuffer,  0, NULL,&WorldBufferData, 0, 0);
		DEVICECONTEXT()->VSSetConstantBuffers(1, 1, &WorldBuffer);
		//쉐이더 사용을 위한 등록

		DEVICECONTEXT()->IASetInputLayout(vertexLayout);
	}
	else
	{
		DEVICECONTEXT()->CSSetShader(this->cs, 0, 0);
	}
}
