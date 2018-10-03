#pragma once
#include "./Singleton/SingletonBase.h"
class D2D : public SingletonBase<D2D>
{
private:
	ID3D11Device * device;	//��ġ ������ �ʿ��� ����
	ID3D11DeviceContext* deviceContext;	//�������� �ʿ��� ����
	//�߿�!! �� �ΰ� ������ ������ ���̷�Ʈ ����� �� �Ѵ�

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* RTV;	//�������
	
public:
	D2D();
	~D2D();

	//Device, DeviceContext, SwapChain
	void CreateDeviceAndSwapChain();
	//BackBuffer
	void CreateBackBuffer();
	//viewport(âũ��)
	void CreateViewport();
	void Clear(D3DXCOLOR color);	//�ĸ���� ���� ����
	void Present();	//�ĸ���� ���� -> �������

	ID3D11Device* GetDevice() { return device; };
	ID3D11DeviceContext* GetDC() { return deviceContext; }
};

#define D2DCLASS() D2D::Get()
#define DEVICE() D2DCLASS()->GetDevice()
#define DEVICECONTEXT() D2DCLASS()->GetDC()
