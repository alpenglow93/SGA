#include "stdafx.h"
#include "PostEffect.h"


PostEffect::PostEffect(wstring file)
	:Material(_Shader + file)
{
	this->SetMaterialMap(file, this);
}

PostEffect::~PostEffect()
{
}

void PostEffect::Update()
{
	if (!bActive) return;
}

void PostEffect::Render()
{
	if (!bActive) return;
	DEVICECONTEXT()->PSSetShaderResources(0, 1, &SRV);
	__super::Render();
}

void PostEffect::Texture(ID3D11ShaderResourceView * SRV)
{
	this->SRV = SRV;
}

void PostEffect::SetInsfector()
{
}
