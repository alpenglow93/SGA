#include "stdafx.h"
#include "ColorShader.h"


ColorShader::ColorShader(wstring file)
	:Material(_Shader + file)
{
	buffer = new Buffer();
	this->SetMaterialMap(file, this);
}


ColorShader::~ColorShader()
{
	SAFE_DELETE(buffer);
}

void ColorShader::Color(D3DXCOLOR color)
{
	buffer->SetColor(color);
}

void ColorShader::Render()
{
	buffer->SetPSBuffer(0);
	__super::Render();
}

void ColorShader::SetInsfector()
{
	ImGui::Checkbox("Color", &bActive);

	ImGui::ColorEdit4("Editor",buffer->Data.Color);

	ImGui::Separator();

}
