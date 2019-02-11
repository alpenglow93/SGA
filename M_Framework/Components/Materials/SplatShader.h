#pragma once
#include "./Material.h"
class SplatShader : public Material
{
public:
	SplatShader(wstring file);
	~SplatShader();

	void Update();
	void Render();

	virtual void SetInsfector() override;

	void Texture(ID3D11ShaderResourceView* control, ID3D11ShaderResourceView** tile);
	void Texture(ID3D11ShaderResourceView* contiol);
	void Tiling(float f);
private:

	struct Buffer : public BufferDesc
	{
	public:
		struct Struct
		{
			float Tiling;
			D3DXVECTOR3 Padding;
		}Data;
		Buffer() : BufferDesc(&Data, sizeof(Struct))
		{
			Data.Tiling = 1.0f;
		}
		void SetTiling(float f)
		{
			Data.Tiling = f;
		}
	};
private:
	Buffer* buffer;

	ID3D11ShaderResourceView* ControlTexture;
	ID3D11ShaderResourceView* TileTexture[4];
};

