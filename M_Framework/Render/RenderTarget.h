#pragma once
#include "./Singleton/SingletonBase.h"
class RenderTarget : public SingletonBase<RenderTarget>
{
private:
	ID3D11Texture2D* renderTargetTexture;
	ID3D11RenderTargetView* renderTargetView;

	ID3D11ShaderResourceView* shaderResourceView; 
public:
	RenderTarget(int width, int height);
	~RenderTarget();

	static RenderTarget* Get(float width = 0, float height = 0);

	void SetRenderTarget();
	
	void Clear(D3DXCOLOR color);
	
	ID3D11ShaderResourceView* Texture() {
		return shaderResourceView;
	};

	void SaveFile(wstring fileName);
};

