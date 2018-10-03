#pragma once
class D2D
{
private:
	ID3D11Device *device;	//장치 생성시 필요한 변수
	ID3D11DeviceContext* deviceContext;	//랜더링에 필요한 변수
	//중요!! 이 두개 변수가 없으면 다이렉트 사용을 못 한다

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* RTV;	//전방버퍼
	
public:
	D2D();
	~D2D();

	//Device, DeviceContext, SwapChain
	void CreateDeviceAndSwapChain();
	//BackBuffer
	void CreateBackBuffer();
	//viewport(창크기)
	void CreateViewport();

	void Clear(D3DXCOLOR color);	//후면버퍼 내용 삭제
	void Present();	//후면버퍼 내용 -> 전방버퍼
};

