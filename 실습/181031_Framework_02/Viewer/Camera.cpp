#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
	:position(0, 0, 0)
{
	this->CreateBuffer();
}


Camera::~Camera()
{
	SAFE_RELEASE(ViewOrthoBuffer);
}

void Camera::Update()
{
	//ī�޶� ����
	D3DXVECTOR3 up = { 0.0f, 1.0f, 0.0f };	//ī�޶��� �� ����
	D3DXVECTOR3 forward = { 0.0f, 0.0f, 1.0f };	//ī�޶��� ����(�Կ�����)

	//View ����
	D3DXMatrixLookAtLH
	(
		&ViewOrthoBufferData.View,	//View ��Ŀ� ����
		&position,
		&(position + forward),
		&up
	);
	D3DXMatrixTranspose(&ViewOrthoBufferData.View, &ViewOrthoBufferData.View);
}

void Camera::CreateBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ViewOrthoBufferDesc);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = DEVICE()->CreateBuffer(&bufferDesc, NULL, &ViewOrthoBuffer);
	assert(SUCCEEDED(hr) && "Not Create View and Ortho Buffer");

	//ortho ����
	D3DXMatrixOrthoOffCenterLH
	(
		&ViewOrthoBufferData.Ortho, 0, desc.Width, 0, desc.Height, 0.0f, 1.0f
	);
	D3DXMatrixTranspose(&ViewOrthoBufferData.Ortho, &ViewOrthoBufferData.Ortho);
}

void Camera::SetBuffers()
{
	DEVICECONTEXT()->UpdateSubresource(ViewOrthoBuffer, 0, NULL, &ViewOrthoBufferData, 0, 0);
	DEVICECONTEXT()->VSSetConstantBuffers(0, 1, &ViewOrthoBuffer);
}

void Camera::Position(D3DXVECTOR2 vec)
{
	//D3DXVECTOR3 == float 3�� 0, 1, 2
	//D3DXVECTOR2 == float 2�� 0, 1
	memcpy(&position, &vec, sizeof(D3DXVECTOR2));
}

void Camera::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Camera::Position(D3DXVECTOR2 * vec)
{
	memcpy(vec, &position, sizeof(D3DXVECTOR2));
}
