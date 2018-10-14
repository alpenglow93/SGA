#include "stdafx.h"
#include "Shader.h"



Shader::Shader()
{
}

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



	this->CreateWVPBuffer();
}

Shader::~Shader()
{
	SAFE_RELEASE(vs);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(WVPBuffer);

	SAFE_RELEASE(vertexLayout);	//추가
}

void Shader::CreateWVPBuffer()
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


void Shader::SetWVPData(D3DXMATRIX World)
{
	//world = 이동, 회전, 크기의 데이터가 들어가 있는 녀석
	WVPBufferData.World = World;
	D3DXMatrixTranspose(&WVPBufferData.World, &WVPBufferData.World);
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

	DEVICECONTEXT()->UpdateSubresource(WVPBuffer, 0, NULL, &WVPBufferData, 0, 0);
	DEVICECONTEXT()->VSSetConstantBuffers(0, 1, &WVPBuffer);


	DEVICECONTEXT()->IASetInputLayout(vertexLayout);
}
