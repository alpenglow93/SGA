#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(wstring file)
	:position(D3DXVECTOR2(0, 0))
	, scale(D3DXVECTOR2(1, 1))
	, rotation(0.0f)
	, srv(NULL)
{
	//텍스쳐 파일 로드
	filePath = L"./_Textures/" + file;
	HRESULT hr;

	srv = Sprites::Load(filePath);

	//셰이더 초기화
	shader = new Shader(L"Sprite.hlsl");
	shader->CreateInputLayout(VertexPT::desc, VertexPT::count);

	//vertices 설정
	vertices = new VertexPT[VertexCount];
	vertices[0].position = { -0.5f, -0.5f, 0.0f };	//왼쪽아래
	vertices[1].position = { -0.5f, 0.5f, 0.0f };	//왼쪽위
	vertices[2].position = { 0.5f, 0.5f, 0.0f };	//오른쪽위

	vertices[3].position = vertices[0].position;
	vertices[4].position = vertices[2].position;
	vertices[5].position = { 0.5f, -0.5f, 0.0f };	//오아

													//texCoord 설정 0 ~ 1
	vertices[0].texCoord = { 0.0f, 1.0f };
	vertices[1].texCoord = { 0.0f, 0.0f };
	vertices[2].texCoord = { 1.0f, 0.0f };

	vertices[3].texCoord = vertices[0].texCoord;
	vertices[4].texCoord = vertices[2].texCoord;
	vertices[5].texCoord = { 1.0f, 1.0f };

	//CreateVertexBuffer
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;	//default 수정
	bufferDesc.ByteWidth = sizeof(VertexPT) * VertexCount;
	//CpuAdress 삭제
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };	//추가
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices;	//추가

	hr = DEVICE()->CreateBuffer(
		&bufferDesc,
		&data, &vertexBuffer);	//NULL->&data 수정
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");

	vertexUVData.offset = { 0, 0 };
	vertexUVData.maxFrame = { 1, 1 };

	this->CreateVertexUVBuffer();
	this->CreateBlendState();
	this->CreateSamplerState();
}

Sprite::~Sprite()
{
	Sprites::Remove(filePath);
	SAFE_RELEASE(blendState[0]);
	SAFE_RELEASE(blendState[1]);
	SAFE_RELEASE(samplerState);
	SAFE_RELEASE(VertexUVBuffer);

	SAFE_DELETE(shader);
	SAFE_DELETE_ARRAY(vertices);

	SAFE_RELEASE(vertexBuffer);
}

void Sprite::CreateBlendState()
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

	desc.RenderTarget[0].BlendEnable = false;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DEVICE()->CreateBlendState(&desc, &blendState[0]);

	desc.RenderTarget[0].BlendEnable = true;
	//화면(dest) + 이미지(src)
	//화면 회색
	//destBlend->픽셀 쉐이더값 출력하는 값의 RGB 값에 곱할 값
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//srcBlend-> 랜더링 대상의 현재 RGB 값에서 곱할 값
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//blendop -> 화면 destBlend, 이미지 srcBlend
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//destBlendAlpha -> 픽셀 쉐이더값 출력하는 값의 Alpha 값에 곱할 값
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	//srcBlendAlpha-> 랜더링 대상의 현재 Alpha 값에서 계산할 값
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	//BlendOpAlpha -> 화면 destBlend, 이미지 srcBlend
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	DEVICE()->CreateBlendState(&desc, &blendState[1]);
}

void Sprite::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	//밉맵 필터 -> 원본 이미지보다 크게, 작게 출력했을때 보정처리
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 1;	//보정 수치 높을수록 깔끔하게 나온다
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//lod -> level of detail

	HRESULT hr = DEVICE()->CreateSamplerState(
		&samplerDesc, &samplerState);
	assert(SUCCEEDED(hr) && "Not Create SamplerState");

}

void Sprite::CreateVertexUVBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(VertexUVDesc);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = DEVICE()->CreateBuffer(
		&bufferDesc, NULL, &VertexUVBuffer
	);
	assert(SUCCEEDED(hr) && "Not Create VertexUVBuffer");
}

void Sprite::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Sprite::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void Sprite::Rotation(float angle)
{
	rotation = angle;
}

void Sprite::Offset(float x, float y)
{
	Offset(D3DXVECTOR2(x, y));
}

void Sprite::Offset(D3DXVECTOR2 offset)
{
	vertexUVData.offset = offset;
}

void Sprite::MaxFrame(float x, float y)
{
	MaxFrame(D3DXVECTOR2(x, y));
}

void Sprite::MaxFrame(D3DXVECTOR2 offset)
{
	vertexUVData.maxFrame = offset;
}

void Sprite::Texture(wstring file)
{
	wstring fileTemp = L"./_Textures/" + file;
	if (fileTemp == filePath) return;

	Sprites::Remove(filePath);
	filePath = fileTemp;
	srv = Sprites::Load(fileTemp);
}

void Sprite::Update()
{
	D3DXMATRIX S, T, R;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T, position.x + scale.x * 0.5f, position.y + scale.y * 0.5f, 1.0f);
	D3DXMatrixRotationZ(&R, rotation);

	shader->SetWVPData(S * R * T);

	DEVICECONTEXT()->UpdateSubresource(VertexUVBuffer, 0, NULL, &vertexUVData, 0, 0);

}

void Sprite::Render()
{
	UINT stride = sizeof(VertexPT);
	UINT offset = 0;

	shader->SetShader();
	DEVICECONTEXT()->VSSetConstantBuffers(2, 1, &VertexUVBuffer);

	DEVICECONTEXT()->PSSetSamplers(0, 1, &samplerState);
	DEVICECONTEXT()->PSSetShaderResources(0, 1, &srv);

	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DEVICECONTEXT()->OMSetBlendState(blendState[1], NULL, 0xff);
	DEVICECONTEXT()->Draw(VertexCount, 0);
	DEVICECONTEXT()->OMSetBlendState(blendState[0], NULL, 0xff);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

map<wstring, Sprites::SpriteDesc> Sprites::descMap;

//이미지가 없으면 새로 생성, 존재하면 기존에 저장된 이미지를 찾아서 변환
ID3D11ShaderResourceView* Sprites::Load(wstring file)
{
	map<wstring, SpriteDesc>::iterator iter = descMap.find(file);
	if (iter != descMap.end())
	{
		iter->second.RefCount++;
		return iter->second.Srv;
	}

	HRESULT hr;
	ID3D11ShaderResourceView* srv;
	D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE(), file.c_str(), NULL, NULL, &srv, &hr
	);
	assert(SUCCEEDED(hr) && "Not Create Texture");

	SpriteDesc spriteDesc;
	spriteDesc.RefCount++;
	spriteDesc.Srv = srv;
	descMap[file] = spriteDesc;

	return spriteDesc.Srv;
}

void Sprites::Remove(wstring file)
{
	map<wstring, SpriteDesc>::iterator iter = descMap.find(file);
	wstring error = file + L"Texture is not Remove";
	assert(iter != descMap.end() && error.c_str());

	descMap[file].RefCount++;
	if (descMap[file].RefCount < 1)
	{
		SAFE_RELEASE(descMap[file].Srv);
		descMap.erase(file);
	}
}
