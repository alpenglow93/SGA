#pragma once
class D2D
{
private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* RTV;

public:
	D2D();
	~D2D();

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();
	void CreateViewport();
	void Clear(D3DXCOLOR color);
	void Present();
};

