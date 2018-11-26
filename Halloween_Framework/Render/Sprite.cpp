#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(wstring file)
{
	Init(file, 0.0f, 0.0f, 0.0f, 0.0f);
}
Sprite::Sprite(wstring file, float endX, float endY)
{
	Init(file, 0.0f, 0.0f, endX, endY);

}
Sprite::Sprite(wstring file, float startX, float startY, float endX, float endY)
{
	Init(file, startX, startY, endX, endY);

}
Sprite::~Sprite()
{

	Sprites::Remove(filePath);
	SAFE_RELEASE(blendState[0]);
	SAFE_RELEASE(blendState[1]);
	SAFE_RELEASE(samplerState);
	SAFE_RELEASE(VertexUVBUffer);

	SAFE_DELETE(shader);
	SAFE_DELETE_ARRAY(vertices);

	SAFE_RELEASE(vertexBuffer);
}
void Sprite::Init(wstring file, float startX, float startY, float endX, float endY)
{
	position = { 0.0f,0.0f };
	scale = { 0.0f,0.0f };
	rotation = 0.0f;
	//�ؽ��� ���� �ε�
	filePath = L"./_Textures/" + file;
	HRESULT hr;

	D3DX11_IMAGE_INFO info;
	D3DX11GetImageInfoFromFile(filePath.c_str(), NULL, &info, &hr);
	assert(SUCCEEDED(hr) && "Not Initialize Image Info");

	srv = Sprites::Load(filePath);
	//���� ������ (����) ? �� : ����
	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	//���̴� �ʱ�ȭ 
	shader = new Shader(L"Sprite.hlsl");
	shader->CreateInputLayout(VertexPT::desc, VertexPT::count);

	//vertices ���� 
	vertices = new VertexPT[VertexCount];
	vertices[0].position = { -0.5f, -0.5f, 0.0f }; //�޾�
	vertices[1].position = { -0.5f,  0.5f, 0.0f }; //����
	vertices[2].position = { 0.5f,  0.5f, 0.0f }; //����

	vertices[3].position = vertices[0].position;
	vertices[4].position = vertices[2].position;
	vertices[5].position = { 0.5f, -0.5f, 0.0f }; //����

												  //texCoord ���� 0 ~ 1 
	vertices[0].texCoord = { startX, endY };
	vertices[1].texCoord = { startX, startY };
	vertices[2].texCoord = { endX, startY };

	vertices[3].texCoord = vertices[0].texCoord;
	vertices[4].texCoord = vertices[2].texCoord;
	vertices[5].texCoord = { endX, endY };

	float sizeX = (endX > 0) ? endX * (float)info.Width : (float)info.Width;
	sizeX -= startX * (float)info.Width;

	float sizeY = (endY > 0) ? endY * (float)info.Height : (float)info.Height;
	sizeY -= startY * (float)info.Height;

	scale = D3DXVECTOR2(sizeX, sizeY);

	//CreateVertexBuffer
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //default ���� 
	bufferDesc.ByteWidth = sizeof(VertexPT) * VertexCount;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //CpuAdress ����

	D3D11_SUBRESOURCE_DATA data = { 0 }; //�߰� 
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices; //�߰� 

	hr = DEVICE()->CreateBuffer(
		&bufferDesc,
		&data, &vertexBuffer);  //NULL->&data ����
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");

	vertexUVData.offset = { 0,0 };
	vertexUVData.maxFrame = { 1,1 };
	this->CreateVertexUVBuffer();
	this->CreateBlendState();
	this->CreateSamplerState();
}

void Sprite::CreateBlendState()
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

	desc.RenderTarget[0].BlendEnable = false;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DEVICE()->CreateBlendState(&desc, &blendState[0]);

	desc.RenderTarget[0].BlendEnable = true;
	//ȭ��(dest) + �̹���(src)
	//ȭ�� ȸ�� 
	//destBlend->�ȼ� ���̴��� ����ϴ� ���� RGB ���� ����� �� 
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//srcBlend-> ������ ����� ���� RGB ������ ���� ����� �� 
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//blendop ->  ȭ��  destBlend, �̹���  srcBlend
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//destBlendAlpha->�ȼ� ���̴��� ����ϴ� ���� Alpha ���� ����� �� 
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	//srcBlendAlpha-> ������ ����� ���� Alpha ������ ����� �� 
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	//BlendOpAlpha ->  ȭ��  destBlend, �̹���  srcBlend
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	DEVICE()->CreateBlendState(&desc, &blendState[1]);
}

void Sprite::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	//�Ӹ� ���� -> ���� �̹��� ���� ũ�� , �۰� ��� ������ ����ó�� 
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 1; //���� ��ġ �������� ��� �ϰ� ���´�.
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS; //���� �ֱ� 
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

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
		&bufferDesc, NULL, &VertexUVBUffer
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
	D3DXMatrixTranslation(&T,position.x + scale.x * 0.5f,position.y + scale.y * 0.5f, 1.0f);

	D3DXMatrixRotationZ(&R, rotation);

	//R * T -> ����
	//T * R -> ���� 
	local = world = S * T * R;

}

void Sprite::Render()
{
	UINT stride = sizeof(VertexPT);
	UINT offset = 0;
	
	shader->SetWVPData(world);
	DEVICECONTEXT()->UpdateSubresource(VertexUVBUffer, 0, NULL, &vertexUVData, 0, 0);
	
	shader->SetShader();
	DEVICECONTEXT()->VSSetConstantBuffers(2, 1, &VertexUVBUffer);
	
	DEVICECONTEXT()->PSSetSamplers(0, 1, &samplerState);
	DEVICECONTEXT()->PSSetShaderResources(0, 1, &srv);
	
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DEVICECONTEXT()->OMSetBlendState(blendState[1], NULL, 0xFF);
	DEVICECONTEXT()->Draw(VertexCount, 0);
	DEVICECONTEXT()->OMSetBlendState(blendState[0], NULL, 0xFF);
}

////////////////////////////////////////////////////////////////////////////////////////////////

map<wstring, Sprites::SpriteDesc> Sprites::descMap;

//�̹����� ������ ���� ���� or �����ϸ� ������ ����� �̹����� ã�Ƽ� ��ȯ
ID3D11ShaderResourceView * Sprites::Load(wstring file)
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

	descMap[file].RefCount--;
	if (descMap[file].RefCount < 1)
	{
		SAFE_RELEASE(descMap[file].Srv);
		descMap.erase(file);
	}
}
