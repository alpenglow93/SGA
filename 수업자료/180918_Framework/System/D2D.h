#pragma once
class D2D
{
private:
	//��ġ ������ �ʿ��� ���� 
	ID3D11Device * device; 
	//�������� �ʿ��� ���� 
	ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;

	ID3D11RenderTargetView* RTV; //������� 

public:
	D2D();
	~D2D();

	//Device, DeviceContext, SwapChain 
	void CreateDeviceAndSwapChain();
	//BackBuffer
	void CreateBackBuffer();
	//viewport(âũ��)
	void CreateViewport();
	//�ĸ���� ������� 
	void Clear(D3DXCOLOR color);
	//�ĸ� ���� ���� -> ������� 
	void Present();
};

