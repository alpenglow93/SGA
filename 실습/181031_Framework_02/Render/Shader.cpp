#include "stdafx.h"
#include "Shader.h"


Shader::Shader(wstring file, string vs, string ps)
{
	//string.c_str()-> char* 형식으로 바꾸겠다

	wstring filePath = L"./Shader/" + file;
	HRESULT hr;
	hr = D3DX11CompileFromFile(
		filePath.c_str(), 0, 0, vs.c_str(), "vs_5_0",
		0, 0, 0, &vsBlob, 0, 0);
	assert(SUCCEEDED(hr) && "Not Compiling VS");

	hr = D3DX11CompileFromFile(
		filePath.c_str(), 0, 0, ps.c_str(), "ps_5_0",
		0, 0, 0, &psBlob, 0, 0);
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

Shader::~Shader()
{
	SAFE_RELEASE(vs);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(WorldBuffer);

	SAFE_RELEASE(vertexLayout);	//추가
}

void Shader::CreateBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(WorldBufferDesc);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = DEVICE()->CreateBuffer(
		&bufferDesc, NULL, &WorldBuffer
	);
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
	assert(vertexLayout != NULL && "Not Initalize Layout");

	//쉐이더 사용을 위한 등록
	DEVICECONTEXT()->VSSetShader(this->vs, 0, 0);
	DEVICECONTEXT()->PSSetShader(this->ps, 0, 0);

	DEVICECONTEXT()->UpdateSubresource(WorldBuffer, 0, NULL, &WorldBufferData, 0, 0);
	DEVICECONTEXT()->VSSetConstantBuffers(1, 1, &WorldBuffer);


	DEVICECONTEXT()->IASetInputLayout(vertexLayout);
}
