#pragma once
#include "./Material.h"


class ColorShader : public Material
{
private:
	struct Buffer : public BufferDesc
	{
	public:
		struct Struct
		{
			D3DXCOLOR Color;
		}Data;

		Buffer() : BufferDesc(&Data, sizeof(Struct))
		{
			Data.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		void SetColor(D3DXCOLOR color)
		{
			Data.Color = color;
		}
	};
private:
	Buffer* buffer;
public:
	ColorShader(wstring file);
	~ColorShader();

	void Color(D3DXCOLOR color);

	virtual void Render() override;

	virtual void SetInsfector() override;

};

