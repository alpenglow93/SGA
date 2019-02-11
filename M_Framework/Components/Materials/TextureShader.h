#pragma once
#include "./Material.h"
class TextureShader : public Material
{
private:

	struct Buffer : public BufferDesc
	{
	public:
		struct Struct
		{
			D3DXVECTOR2 Start;
			D3DXVECTOR2 End;
		}Data;
		Buffer() : BufferDesc(&Data, sizeof(Struct))
		{
			Data.Start = { 0.0f, 0.0f };
			Data.End = { 1.0f,1.0f };
		}
		void SetStart(D3DXVECTOR2 start)
		{
			Data.Start = start;
		}
		void SetEnd(D3DXVECTOR2 end)
		{
			Data.End = end;
		}
	};
	Buffer* buffer;
	ID3D11ShaderResourceView* SRV;
	D3DX11_IMAGE_INFO info;

	char str[32] = "";
public:
	TextureShader(wstring file);
	~TextureShader();

	void Update() override;
	void Render() override;

	void Texture(ID3D11ShaderResourceView* SRV);
	void Texture(ID3D11ShaderResourceView* SRV, D3DX11_IMAGE_INFO info);
	void Start(D3DXVECTOR2 vec);
	void Start(float x, float y);
	void End(D3DXVECTOR2 vec);
	void End(float x, float y);
	virtual void SetInsfector() override;

};

