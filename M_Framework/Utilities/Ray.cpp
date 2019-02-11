#include "stdafx.h"
#include "Ray.h"
#include "./Components/Transform.h"
#include "./Components/Materials/ColorShader.h"
#include "./Components/Collider/SphereCollider.h"
#include "./Components/Collider/BoxCollider.h"
#include "./Utilities/Math.h"
Ray::Ray()
{
	Origin = { 0.0f,0.0f };
	Direction = { 1.0f,0.0f };
	Initialize();
}

Ray::Ray(D3DXVECTOR2 & origin, D3DXVECTOR2 & direction)
	:Origin(origin), Direction(direction)
{
	Initialize();
}


Ray::~Ray()
{
	SAFE_RELEASE(buffer);
}

void Ray::Initialize()
{
	transform = new Transform;
	shader = Materials::Get()->Load<ColorShader>(L"Effect.hlsl");

	Vertex* vertice = new Vertex[2];
	vertice[0].position = { 0.0f,0.0f,0.0f };
	vertice[1].position = { 1.0f,0.0f,0.0f };

	CreateVertexBuffer(&buffer, vertice, sizeof(Vertex) * 2);
	SAFE_DELETE_ARRAY(vertice);
}

void Ray::Update()
{
	transform->SetWorldPosition(Origin);
	transform->LookDirection(Origin + Direction);
	transform->Scale(1000.0f,1.0f);

	transform->Update();
}

void Ray::Render()
{
	shader->Render();
	transform->Render();
	UINT offset = sizeof(Vertex);
	UINT stride = 0;
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	DEVICECONTEXT()->Draw(2, 0);
}

void Ray::SetOrigin(float x, float y)
{
	Origin.x = x;
	Origin.y = y;
}

void Ray::SetDirection(float x, float y)
{
	Direction.x = x;
	Direction.y = y;
}

void Ray::SetTarget(float x, float y)
{
	D3DXVECTOR2 target = D3DXVECTOR2(x, y);
	D3DXVec2Normalize(&Direction, &(target - Origin));
}

bool Ray::Raycast(SphereCollider * collider, D3DXVECTOR2 * point, D3DXVECTOR2 * normal)
{
	D3DXVECTOR2 center;
	float radius;
	collider->GetWorldCenterRadius(&center, &radius);

	D3DXVECTOR2 dir = center - Origin;
	
	float length = D3DXVec2Length(&dir);

	if (radius > length) return false; //원안에서 ray가 시작할때 
	
	D3DXVec2Normalize(&dir, &dir);

	float dot = D3DXVec2Dot(&Direction, &dir); 

	if (dot <= 0.0f)return false;//원까지의 방향과 레이의 방향이 다를경우

	//dot -> 길이 (정규화)

	// 1 : dot = Length : d -> d = dot * Length

	//dot = 1.0f - dot;
	float temp = dot * length;
	float d = sqrtf(length * length - temp * temp);

	if (d > radius) return false;

	
	if (point != NULL)
	{
		float teltaX = temp - sqrtf(radius * radius - d * d);

		*point = Origin + Direction * teltaX;
		if (normal != NULL)
		{
			*normal = *point - center;
			D3DXVec2Normalize(normal, normal);
		}
	}
	return true;
}

bool Ray::Raycast(BoxCollider * collider, D3DXVECTOR2 * point, D3DXVECTOR2 * normal)
{
	D3DXVECTOR2 cp[4];
	D3DXVECTOR2 center;
	collider->GetWorldVertices(cp, &center);

	D3DXVECTOR2 dir = center - Origin;

	float length = D3DXVec2Length(&dir);

	D3DXVec2Normalize(&dir, &dir);
	float dot = D3DXVec2Dot(&dir, &Direction);
	if (dot <= 0.0f) return false;


	//직선 직선의 교차점
	//방향 -> 선분
	//시작 -> 반직선
	//시작, 끝 -> 직선

	//vec2 a, b -> 시작, 끝
	//vec2 c, d -> 시작, 끝
	//det = (b - a).cross(d - c)
	//vec a + (b - a)(방향)(c - a).cross(d-c) /det) 
	vector<float> result;
	for (int i = 0;i < 4; i++)
	{
		//a(Origin) b(ray 끝) -> ray
		//b - a 방향
		//c(i) d-> (i+1) -> cp
	
		D3DXVECTOR2 dir1 = Origin - cp[i];
		D3DXVECTOR2 dir2 = Origin - cp[(i + 1) % 4];
		D3DXVec2Normalize(&dir1, &dir1);
		D3DXVec2Normalize(&dir2, &dir2);

		float cross1 = Math::Vec2Cross(Direction, dir1);
		float cross2 = Math::Vec2Cross(Direction ,dir2);

		if (cross1 * cross2  < 0.0f ) 
		{
			float det = Math::Vec2Cross(Direction * 1000, cp[(i + 1) % 4] - cp[i]);
			D3DXVECTOR2 vec = Origin + Direction * 1000
				* Math::Vec2Cross(cp[i] - Origin, cp[(i+1)%4]- cp[i]) / det;
			
			result.push_back(D3DXVec2Length(&(Origin - vec)));
		}
	}
	float min;
	if (result.size() > 0)
	{
		min = result[0];
		if (result.size() > 1)
		{
			for (int i = 1; i < result.size(); i++)
			{
				if (min > result[i])
					min = result[i];
			}
		}

		if (point != NULL)
		{
			*point = Origin + Direction * min;
			if (normal != NULL)
			{

			}
		}

		return true;
	}
	

	return false;
}
