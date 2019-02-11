#include "stdafx.h"
#include "TextureShader.h"


TextureShader::TextureShader(wstring file)
	:Material(_Shader + file)
{
	SRV = NULL;
	buffer = new Buffer;
	this->SetMaterialMap(file, this);
}

TextureShader::~TextureShader()
{
	SAFE_DELETE(buffer);
}

void TextureShader::Update()
{
	if (!bActive) return;
}

void TextureShader::Render()
{
	if (!bActive) return;
	if(SRV != NULL)
		DEVICECONTEXT()->PSSetShaderResources(0, 1, &SRV);
	buffer->SetVSBuffer(2);
	__super::Render();
}

void TextureShader::Texture(ID3D11ShaderResourceView * SRV)
{
	this->SRV = SRV;
}

void TextureShader::Texture(ID3D11ShaderResourceView * SRV, D3DX11_IMAGE_INFO info)
{
	this->SRV = SRV;
	this->info = info;
}

void TextureShader::Start(D3DXVECTOR2 vec)
{
	buffer->SetStart(D3DXVECTOR2(vec.x , vec.y));
}

void TextureShader::Start(float x, float y)
{
	Start(D3DXVECTOR2(x, y));
}

void TextureShader::End(D3DXVECTOR2 vec)
{
	buffer->SetEnd(D3DXVECTOR2(vec.x , vec.y));
}

void TextureShader::End(float x, float y)
{
	End(D3DXVECTOR2(x, y));
}
void TextureShader::SetInsfector()
{
	if (ImGui::BeginChild("Insfactor",ImVec2(0,0),false,
		ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Checkbox("Material", &bActive);
		ImGui::PushItemWidth(140);
		ImGui::InputText("File", str, 32);
		ImGui::SameLine();
		if (ImGui::Button("Load"))
		{
			string temp = str;
			SRV = Sprites::Load(_Texture + String::ToWString(temp));
			info = Sprites::Info(_Texture + String::ToWString(temp));
		}
		ImGui::Image(SRV, ImVec2(150, 150));
		ImGui::LabelText("Size", "%d, %d", info.Width, info.Height);
		ImGui::InputFloat2("Start", buffer->Data.Start);
		ImGui::InputFloat2("End", buffer->Data.End);

		ImGui::EndChild();
	}
	ImGui::Separator();
}
