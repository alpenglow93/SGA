#pragma once
#include "./Singleton/SingletonBase.h"
class D2D : public SingletonBase<D2D>
{
private:
	//��ġ ������ �ʿ��� ���� 
	ID3D11Device * device; 
	//�������� �ʿ��� ���� 
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* RTV; //������� 

	UINT numerator;
	UINT denominator;

	UINT gpuMemorySize;
	wstring gpuDescription;


public:
	D2D();
	~D2D();


	void SetGpuInfo();
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

	ID3D11Device* GetDeivce() { return device; };
	ID3D11DeviceContext* GetDC() { return deviceContext; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }
};

#define D2DCLASS() D2D::Get()
#define DEVICE() D2DCLASS()->GetDeivce()
#define DEVICECONTEXT() D2DCLASS()->GetDC()