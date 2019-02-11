#include "stdafx.h"
#include "Camera.h"
#include "./Objects/Object.h"
#include "./Transform.h"
Camera::Camera(class Object* obj) 
{
	transform = obj->GetComponent<Transform>();
	Buffer = new ViewOrtho;
}
Camera::~Camera()			
{
	SAFE_DELETE(Buffer);
}

void Camera::Update()
{
	D3DXMATRIX view, ortho;
	D3DXVECTOR3 vEye;
	vEye.x = transform->GetWorldPosition().x;
	vEye.y = transform->GetWorldPosition().x;
	vEye.z = 0.0f;
	D3DXVECTOR3 vAt = vEye;
	vAt.z = 1.0f;

	D3DXMatrixLookAtLH
	(
		&view, &vEye, &vAt, new D3DXVECTOR3(0, 1, 0)
	);
	//2D
	D3DXMatrixOrthoOffCenterLH
	(
		&ortho, 0, desc.Width, 0, desc.Height, 0.0f,
		10.0f
	);

	SetViewOrhto(&view, &ortho);
	//3D
	/*D3DXMATRIX perspective;
	D3DXMatrixPerspectiveFovLH(
		&perspective, D3DXToRadian(60.0f),
		desc.Width / desc.Height, 0.1f, 1000.0f
	);*/
}
void Camera::Render()	
{
	Buffer->Change();
}

void Camera::SetViewOrhto(D3DXMATRIX* view, D3DXMATRIX* ortho)	
{
	Buffer->SetView(*view);
	if (ortho != NULL)
	{
		Buffer->SetOrtho(*ortho);
	}
}
D3DXMATRIX Camera::GetViewOrhto()
{
	return Buffer->Get();
}

void Camera::SetInsfector()
{
}
