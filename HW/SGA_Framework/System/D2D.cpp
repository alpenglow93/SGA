#include "stdafx.h"
#include "D2D.h"


D2D::D2D()
{
	this->CreateDeviceAndSwapChain();
	this->CreateBackBuffer();
	this->CreateViewport();
}


D2D::~D2D()
{
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(RTV);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}

void D2D::CreateDeviceAndSwapChain()
{
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = desc.Width;
	bufferDesc.Height = desc.Height;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChindesc;
	ZeroMemory(&swapChindesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChindesc.BufferDesc = bufferDesc;
	swapChindesc.SampleDesc.Count = 1;
	swapChindesc.SampleDesc.Quality = 0;
	swapChindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChindesc.BufferCount = 1;
	swapChindesc.OutputWindow = desc.Handle;
	swapChindesc.Windowed = !desc.bFullScreen;
	swapChindesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChindesc, &swapChain,
		&device, NULL, &deviceContext
	);
	assert(SUCCEEDED(hr) && "Not Initialize Device");
}

void D2D::CreateBackBuffer()
{
	HRESULT hr;
	ID3D11Texture2D* backbuffer;
	hr = swapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D), (void**)&backbuffer);

	assert(SUCCEEDED(hr) && "Not Get SwapChain Data");

	hr = device->CreateRenderTargetView(backbuffer, NULL, &RTV);
	assert(SUCCEEDED(hr) && "Not Get Create RTV");

	deviceContext->OMSetRenderTargets(1, &RTV, NULL);

}

void D2D::CreateViewport()
{
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = desc.Width;
	viewport.Height = desc.Height;

	deviceContext->RSSetViewports(1, &viewport);
}

void D2D::Clear(D3DXCOLOR color)
{
	deviceContext->ClearRenderTargetView(RTV, color);
}

void D2D::Present()
{
	swapChain->Present(0, 0);
}