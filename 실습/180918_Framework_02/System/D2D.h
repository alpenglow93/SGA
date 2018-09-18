#pragma once
class D2D
{
private:
	ID3D11Device *device;	//��ġ ������ �ʿ��� ����
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
};

