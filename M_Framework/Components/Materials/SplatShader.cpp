#include "stdafx.h"
#include "SplatShader.h"


SplatShader::SplatShader(wstring file)
	:Material(_Shader + file)
{
	buffer = new Buffer;
	CreateSampler();
}
SplatShader::~SplatShader()
{
	SAFE_DELETE(buffer);
}
void SplatShader::Update()
{
	DEVICECONTEXT()->PSSetShaderResources(0, 1, &ControlTexture);
	DEVICECONTEXT()->PSSetShaderResources(1, 4, TileTexture);
	__super::Update();
}
void SplatShader::Render()
{
	DEVICECONTEXT()->PSSetSamplers(0, 1, &SamplerWrap);
	buffer->SetPSBuffer(0);
	__super::Render();
}

void SplatShader::SetInsfector()
{
	ImGui::BeginChild("Insfactor");
	{
		ImGui::Checkbox("Splat Matertial", &bActive);
		ImGui::Image(ControlTexture, ImVec2(200, 200));
		for (int i = 0; i < 4; i++)
		{
			ImGui::Image(TileTexture[i], ImVec2(100, 100));
			if (i % 2 == 0) ImGui::SameLine();
		}
		ImGui::SliderFloat("Tiling", &buffer->Data.Tiling, 1.0f, 255.0f);
	}
	ImGui::EndChild();
}

void SplatShader::Texture(ID3D11ShaderResourceView * control, ID3D11ShaderResourceView ** tile)
{
	ControlTexture = control;
	for(int i =0 ; i< 4; i++)
		TileTexture[i] = tile[i];
}

void SplatShader::Texture(ID3D11ShaderResourceView * control)
{
	ControlTexture = control;
}

void SplatShader::Tiling(float f)
{
	buffer->SetTiling(f);
}
