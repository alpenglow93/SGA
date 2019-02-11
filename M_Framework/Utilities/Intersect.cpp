#include "stdafx.h"
#include "Intersect.h"
#include "./Components/Collider/BoxCollider.h"
#include "./Components/Collider/SphereCollider.h"
Intersect::Intersect()
{
}
Intersect::~Intersect()
{
}

float Intersect::GetAngle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2)
{
	D3DXVECTOR2 delta = pos2 - pos1;

	float distance = D3DXVec2Length(&delta);

	float angle = acosf(delta.x / distance);

	if (pos1.y > pos2.y)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}
	return angle;
}

float Intersect::GetAngle(SphereCollider * comp1, SphereCollider * comp2)
{
	D3DXVECTOR2 center1, center2;
	float radius1, radius2;

	comp1->GetWorldCenterRadius(&center1, &radius1);
	comp2->GetWorldCenterRadius(&center2, &radius2);

	return Intersect::GetAngle(center1, center2);
}
////////////////////////////////////////////////////////////
///return : result
///comp1 : BoxCollider 1
///comp2 : BoxColluder 2
////////////////////////////////////////////////////////////
bool Intersect::IsConstainsRect(BoxCollider * comp1, BoxCollider * comp2)
{
	if (!comp1->Active()) return false;
	if (!comp2->Active()) return false;

	bool isVertical = false;
	bool isHorizontal = false;
	
	Vertex* rc1 = NULL;
	Vertex* rc2 = NULL;

	UINT vc1;
	UINT vc2;

	D3DXMATRIX W1;
	D3DXMATRIX W2;

	comp1->GetVertexAndWorld(&rc1, vc1, W1);
	comp2->GetVertexAndWorld(&rc2, vc2, W2);

	Vertex vec1[5];
	Vertex vec2[5];

	for (int i = 0; i < vc1; i++)
	{
		D3DXVec3TransformCoord(&vec1[i].position, &rc1[i].position, &W1);
		D3DXVec3TransformCoord(&vec2[i].position, &rc2[i].position, &W2);
	}

	D3DXVECTOR3 MinMax[2][2];

	MinMax[0][0] = vec1[0].position;
	MinMax[0][1] = vec1[0].position;

	MinMax[1][0] = vec2[0].position;
	MinMax[1][1] = vec2[0].position;

	for (int i = 1; i < vc1;i++)
	{
		if (MinMax[0][0].x > vec1[i].position.x)
			MinMax[0][0].x = vec1[i].position.x;

		if (MinMax[1][0].x > vec2[i].position.x)
			MinMax[1][0].x = vec2[i].position.x;

		if (MinMax[0][0].y > vec1[i].position.y)
			MinMax[0][0].y = vec1[i].position.y;
											  
		if (MinMax[1][0].y > vec2[i].position.y)
			MinMax[1][0].y = vec2[i].position.y;

		if (MinMax[0][1].x < vec1[i].position.x)
			MinMax[0][1].x = vec1[i].position.x;

		if (MinMax[1][1].x < vec2[i].position.x)
			MinMax[1][1].x = vec2[i].position.x;

		if (MinMax[0][1].y < vec1[i].position.y)
			MinMax[0][1].y = vec1[i].position.y;
						
		if (MinMax[1][1].y < vec2[i].position.y)
			MinMax[1][1].y = vec2[i].position.y;
	}

	if (MinMax[0][0].x <= MinMax[1][1].x 
		&& MinMax[0][1].x >= MinMax[1][0].x)
	{
		isHorizontal = true;
	}
	if (MinMax[0][0].y <= MinMax[1][1].y 
		&& MinMax[0][1].y >= MinMax[1][0].y)
	{
		isVertical = true;
	}
	if (isHorizontal && isVertical)
	{
		return true;
	}
	return false;
}

bool Intersect::IsConstainsCircle(SphereCollider * comp1, SphereCollider * comp2)
{

	//센터 사이의 길이 반지름 끼리 더해서 비교
	D3DXVECTOR2 center1, center2;
	float radius1, radius2;

	comp1->GetWorldCenterRadius(&center1, &radius1);
	comp2->GetWorldCenterRadius(&center2, &radius2);

	float distance = D3DXVec2Length(&(center1 - center2));

	if (distance < radius1 + radius2)
		return true;

	return false;
}

bool Intersect::IsConstainsPoint(SphereCollider * comp1, D3DXVECTOR3 pos)
{
	D3DXVECTOR2 center1;
	float radius1;

	comp1->GetWorldCenterRadius(&center1, &radius1);

	D3DXVECTOR2 temp;
	temp.x = center1.x - pos.x;
	temp.y = center1.y - pos.y;

	float distance = D3DXVec2Length(&(temp));

	if (distance < radius1)
		return true;

	return false;
}

//
//bool Intersect::IsOBB(Rect * comp1, Rect * comp2)
//{
//	ObbDesc ObbA, ObbB;
//	D3DXVECTOR2 LengthA = comp1->GetScale() * 0.5f;
//	CreateObb(&ObbA, comp1, LengthA);
//
//	D3DXVECTOR2 LengthB = comp2->GetScale() * 0.5f;
//	CreateObb(&ObbB, comp2, LengthB);
//
//	return CheckObb(ObbA, ObbB);
//}
//
//void Intersect::CreateObb(ObbDesc * out, Rect * comp, D3DXVECTOR2 length)
//{
//	out->Position = comp->GetPosition() + comp->GetScale() * 0.5f;
//	out->Length[0] = length.x;
//	out->Length[1] = length.y;
//	D3DXMATRIX World = comp->GetWorld();
//	out->Direction[0] = D3DXVECTOR2(World._11, World._12);
//	out->Direction[1] = D3DXVECTOR2(World._21, World._22);
//
//	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
//	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);
//}

float Intersect::SeparateAxis(D3DXVECTOR2 & separate, D3DXVECTOR2 & e1, D3DXVECTOR2 & e2)
{
	float r1 = fabs(D3DXVec2Dot(&separate, &e1));
	float r2 = fabs(D3DXVec2Dot(&separate, &e2));

	return r1 + r2;
}

bool Intersect::CheckObb(ObbDesc & obbA, ObbDesc & obbB)
{
	D3DXVECTOR2 nea1 = obbA.Direction[0], ea1 = nea1 * obbA.Length[0];
	D3DXVECTOR2 nea2 = obbA.Direction[1], ea2 = nea2 * obbA.Length[1];
	D3DXVECTOR2 neb1 = obbB.Direction[0], eb1 = neb1 * obbB.Length[0];
	D3DXVECTOR2 neb2 = obbB.Direction[1], eb2 = neb2 * obbB.Length[1];
	D3DXVECTOR2 distance = obbA.Position - obbB.Position;

	float LengthA = D3DXVec2Length(&ea1);
	float LengthB = SeparateAxis(nea1, eb1, eb2);
	float Length = fabs(D3DXVec2Dot(&distance, &nea1));
	if (Length > LengthA + LengthB) return false;

	LengthA = D3DXVec2Length(&ea2);
	LengthB = SeparateAxis(nea2, eb1, eb2);
	Length = fabs(D3DXVec2Dot(&distance, &nea2));
	if (Length > LengthA + LengthB) return false;

	LengthA = SeparateAxis(neb1, ea1, ea2);
	LengthB = D3DXVec2Length(&eb1);
	Length = fabs(D3DXVec2Dot(&distance, &neb1));
	if (Length > LengthA + LengthB) return false;

	LengthA = SeparateAxis(neb2, ea1, ea2);
	LengthB = D3DXVec2Length(&eb2);
	Length = fabs(D3DXVec2Dot(&distance, &neb2));
	if (Length > LengthA + LengthB) return false;

	return true;
}
