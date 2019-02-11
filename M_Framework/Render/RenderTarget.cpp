#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(int width, int height)
{
	D3D11_TEXTURE2D_DESC textureDesc = { 0 };
	
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET| D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	HRESULT hr = DEVICE()->CreateTexture2D(&textureDesc, NULL,
		&renderTargetTexture);
	assert(SUCCEEDED(hr));

	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
	RTVDesc.Format = textureDesc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;

	hr = DEVICE()->CreateRenderTargetView(
		renderTargetTexture, &RTVDesc, &renderTargetView
	);
	assert(SUCCEEDED(hr));
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	SRVDesc.Format = textureDesc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = DEVICE()->CreateShaderResourceView(
		renderTargetTexture, &SRVDesc, &shaderResourceView
	);
	assert(SUCCEEDED(hr));
}

RenderTarget::~RenderTarget()
{
	SAFE_RELEASE(shaderResourceView);
	SAFE_RELEASE(renderTargetView);
	SAFE_RELEASE(renderTargetTexture);
}

RenderTarget* RenderTarget::Get(float width, float height)
{
	if(instance == NULL)
		instance = new RenderTarget(width, height);

	return instance;
}

void RenderTarget::SetRenderTarget()
{
	DEVICECONTEXT()->OMSetRenderTargets(1, &renderTargetView, NULL);
}

void RenderTarget::Clear(D3DXCOLOR color)
{
	SetRenderTarget();
	DEVICECONTEXT()->ClearRenderTargetView(renderTargetView, color);

}

void RenderTarget::SaveFile(wstring fileName)
{
	D3DX11SaveTextureToFile
	(
		DEVICECONTEXT(),
		renderTargetTexture,
		//(ID3D11Resource*)shaderResourceView,
		D3DX11_IFF_PNG,
		fileName.c_str()
	);
}
