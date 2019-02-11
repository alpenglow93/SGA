#include "stdafx.h"
#include "Material.h"

Material::Material(wstring file, string vs, string ps)
{
	shader = new Shader(file, false);
	shader->CreateInputLayout(VertexPT::desc, VertexPT::count);
}

Material::~Material()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(SamplerWrap);
}

void Material::World(D3DXMATRIX World)
{
	shader->SetWVPData(World);
}

void Material::CreateInputLayOut(D3D11_INPUT_ELEMENT_DESC * desc, UINT count)
{
	shader->CreateInputLayout(desc, count);
}

void Material::Render()
{
	shader->SetShader();
}

void Material::SetMaterialMap(wstring file, Material * mat)
{
	Materials::Get()->MaterialMap[file] = mat;
}

ID3D11SamplerState* Material::SamplerWrap = NULL;

void Material::CreateSampler()
{
	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));

	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	DEVICE()->CreateSamplerState(&SamplerDesc, &SamplerWrap);
}

void Material::SetInsfector()
{
}

///////////////////////////////////////////////////////////////////////////////////////

Materials::Materials()
{
}

Materials::~Materials()
{
	for (pair<wstring, Material*> temp : MaterialMap)
	{
		SAFE_DELETE(temp.second);
	}
}
