#pragma once
#include "./Singleton/SingletonBase.h"
class D2D : public SingletonBase<D2D>
{
private:
	//장치 생성시 필요한 변수 
	ID3D11Device * device; 
	//랜더링에 필요한 변수 
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* RTV; //전방버퍼 

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
	//viewport(창크기)
		void CreateViewport();
	//후면버퍼 내용삭제 
	void Clear(D3DXCOLOR color);
	//후면 버퍼 내용 -> 전방버퍼 
	void Present();

	ID3D11Device* GetDeivce() { return device; };
	ID3D11DeviceContext* GetDC() { return deviceContext; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }
};

#define D2DCLASS() D2D::Get()
#define DEVICE() D2DCLASS()->GetDeivce()
#define DEVICECONTEXT() D2DCLASS()->GetDC()