#include "stdafx.h"
#include "BoxCollider.h"
#include "./Components/Camera.h"
#include "./Components/Transform.h"
#include "./Components/Materials/ColorShader.h"
BoxCollider::BoxCollider(Object * obj)
	:Collider(obj)
{
	size = { 1.0f,1.0f };
	center = { 0.0f,0.0f };

	vertexCount = 5;
	vertices = new Vertex[vertexCount];
	vertices[0].position = {-50.0f,-50.0f, 0.0f };
	vertices[1].position = {-50.0f, 50.0f, 0.0f };
	vertices[2].position = { 50.0f, 50.0f, 0.0f };
	vertices[3].position = { 50.0f,-50.0f, 0.0f };
	vertices[4].position = {-50.0f,-50.0f, 0.0f };

	CreateVertexBuffer(&vertexBuffer, vertices, sizeof(Vertex) * vertexCount);
}

BoxCollider::~BoxCollider()
{
	//SAFE_DELETE_ARRAY(ctrolp);
}

void BoxCollider::Update()
{
	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, center.x, center.y, 0.0f);

	D3DXMATRIX S;
	D3DXMatrixScaling(&S, size.x, size.y, 1.0f);

	World = S * T;
}

void BoxCollider::Render()
{
	__super::Render();
}

void BoxCollider::Center(float x, float y)
{
	center = { x, y };
}

void BoxCollider::Size(float x, float y)
{
	size = { x, y };
}


bool BoxCollider::IsOverlapWithMouse(class Camera* camera)
{
	D3DXMATRIX view = camera->GetViewOrhto();
	D3DXMATRIX invView;

	D3DXMatrixInverse(&invView, NULL, &view);

	mouse = { vMouse.x, vMouse.y, -100.0f };

	D3DXVec3TransformCoord(&mouse, &mouse, &invView);

	ctrolp = new D3DXVECTOR3[vertexCount];
	for (int i = 0; i < vertexCount; i++)
		D3DXVec3TransformCoord(ctrolp + i, &vertices[i].position, &(World *transform->World()));
		//ctrolp[i] = vertices[i].position;

	bool b = true;

	dir = mouse;
	dir.z = 1.0f;


	//b |= D3DXIntersectTri(&ctrolp[0], &ctrolp[1], &ctrolp[2],
	//	&mouse, &dir, NULL, NULL, new float(1000));
	//b |= D3DXIntersectTri(&ctrolp[2], &ctrolp[3], &ctrolp[4],
	//	&mouse, &dir, NULL, NULL, new float(1000));

	b &= mouse.x > ctrolp[0].x;
	b &= mouse.y > ctrolp[0].y;
	b &= mouse.x < ctrolp[2].x;
	b &= mouse.y < ctrolp[2].y;

	return b;
}


void BoxCollider::SetInsfector()
{
	ImGui::BeginChild("Insfactor");
	{
		ImGui::Checkbox("BoxCollider", &bActive);
		matertial->SetInsfector();
	}
	ImGui::EndChild();
}

void BoxCollider::GetWorldVertices(D3DXVECTOR2 * vertex, D3DXVECTOR2* center)
{
	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR2 temp;
		temp.x = vertices[i].position.x;
		temp.y = vertices[i].position.y;

		D3DXVec2TransformCoord(&vertex[i], &temp, &(World * transform->World()));
	}

	D3DXVec2TransformCoord(center, &this->center, &(World * transform->World()));
}
