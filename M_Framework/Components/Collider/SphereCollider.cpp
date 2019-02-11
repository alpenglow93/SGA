#include "stdafx.h"
#include "SphereCollider.h"
#include "./Components/Camera.h"
#include "./Components/Transform.h"

SphereCollider::SphereCollider(Object * obj)
	:Collider(obj)
{
	Radius = 70.0f;
	Center = D3DXVECTOR2(0.0f,0.0f);

	vertices = new Vertex[37];
	float phiStep = 2 * D3DX_PI / 36;
	for (int i = 0; i <= 36;i++)
	{
		vertices[i] = D3DXVECTOR3(
			cosf(phiStep * i),
			sinf(phiStep * i),
			0.0f);
	}
	vertexCount = 37;
	CreateVertexBuffer(&vertexBuffer, vertices,
		sizeof(Vertex) * 37);
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Update()
{
	D3DXMATRIX S, T;
	D3DXMatrixTranslation(&T, Center.x, Center.y, 0.0f);

	D3DXMatrixScaling(&S, Radius, Radius, 1.0f);
	World = S * T;
	__super::Update();
}

void SphereCollider::Render()
{
	__super::Render();
}

void SphereCollider::SetCenter(float x, float y)
{
	Center = { x, y };
}

void SphereCollider::SetRadius(float r)
{
	Radius = r;
}

void SphereCollider::GetWorldCenterRadius(OUT D3DXVECTOR2 * center, OUT float * radius)
{
	D3DXMATRIX final = World * transform->World();

	D3DXVECTOR3 scale;
	D3DXQUATERNION quat;
	D3DXVECTOR3 position;

	D3DXMatrixDecompose(&scale, &quat, &position, &final);
	
	center->x = position.x;
	center->y = position.y;
	*radius = Radius;
}

bool SphereCollider::IsOverlapWithMouse(Camera * camera)
{
	D3DXVECTOR2 temp;
	D3DXMATRIX view = camera->GetViewOrhto();
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXVec2TransformCoord(&temp, &Center, &(World * invView));

	temp.x -= vMouse.x;
	temp.y -= vMouse.y;

	float distance = D3DXVec2Length(&temp);

	if(distance > Radius)
		return false;

	return true;
}
