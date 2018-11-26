#include "stdafx.h"
#include "Intersect.h"


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

float Intersect::GetAngle(Circle * comp1, Circle * comp2)
{
	D3DXVECTOR3 center1 = comp1->GetCenter();
	D3DXVECTOR3 center2 = comp2->GetCenter();

	D3DXVECTOR3 delta = center2 - center1;

	float distance = D3DXVec3Length(&delta);

	float angle = acosf(delta.x / distance);

	if (center1.y > center2.y)
	{
		angle = 2 * D3DX_PI - angle;
		if (angle >= 2 * D3DX_PI) angle -= 2 * D3DX_PI;
	}
	return angle;
}
bool Intersect::IsConstainRect(Rect * temp, Rect * comp1, Rect * comp2)
{
	RECT tempRc, rc1, rc2;

	rc1 = comp1->GetRect();
	rc2 = comp2->GetRect();

	return IntersectRect(&tempRc, &rc1, &rc2);
}

bool Intersect::IsConstainRect(Rect * comp1, D3DXMATRIX mat1, Rect * comp2, D3DXMATRIX mat2)
{
	bool isVertical = false;
	bool isHorizontal = false;
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	comp1->GetRect(&left1, &right1, &top1, &bottom1);
	comp2->GetRect(&left2, &right2, &top2, &bottom2);

	D3DXVECTOR3 vec1[2] =
	{
		D3DXVECTOR3(left1,top1,0),
		D3DXVECTOR3(right1,bottom1,0)
	};
	D3DXVECTOR3 vec2[2] =
	{
		D3DXVECTOR3(left2,top2,0),
		D3DXVECTOR3(right2,bottom2,0)
	};
	//world -> 이동 회전 크기에 대한 데이터 
	//Transform -> 이동 회전 크기를 변경시키는 녀석 
	//Coord -> 좌표 
	for (int i = 0; i < 2; i++)
	{
		D3DXVec3TransformCoord(&vec1[i], &vec1[i], &mat1);
		D3DXVec3TransformCoord(&vec2[i], &vec2[i], &mat2);
	}
	if (vec1[0].x <= vec2[1].x && vec1[1].x >= vec2[0].x)
	{
		isHorizontal = true;
	}
	if (vec1[0].y >= vec2[1].y && vec1[1].y <= vec2[0].y)
	{
		isVertical = true;
	}
	if (isHorizontal && isVertical)
	{
		return true;
	}
	return false;
}

bool Intersect::IsConstainsCircle(Circle * comp1, Circle * comp2)
{
	D3DXVECTOR3 center1, center2;
	float radius1, radius2;
	center1 = comp1->GetCenter();
	radius1 = comp1->GetRadius();

	center2 = comp2->GetCenter();
	radius2 = comp2->GetRadius();

	float deltaX = abs(center1.x - center2.x);
	float deltaY = abs(center1.y - center2.y);

	//sqrtf(루트)
	float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);

	if (distance < radius1 + radius2)
		return true;

	return false;
}

bool Intersect::IsConstainsPoint(Circle * comp, D3DXVECTOR3 mouse)
{
	D3DXVECTOR3 center = comp->GetCenter();
	float radius = comp->GetRadius();

	D3DXVECTOR3 delta = center - mouse;
	float distance = D3DXVec3Length(&delta);

	if (distance < radius)
		return true;

	return false;
}

bool Intersect::IsConstainsPoint(Rect * comp, D3DXVECTOR3 mouse)
{
	RECT AABB = comp->GetRect();

	bool bResult = true;
	//a = a + b -> a += b -> a = a && b -> a &= b; 
	bResult &= AABB.left < mouse.x;
	bResult &= AABB.right > mouse.x;
	bResult &= AABB.top < mouse.y;
	bResult &= AABB.bottom > mouse.y;

	return bResult;
}


bool Intersect::IsOBB(Rect * comp1, Rect * comp2)
{
	ObbDesc ObbA, ObbB;
	D3DXVECTOR2 LengthA = comp1->GetScale() * 0.5f;
	CreateObb(&ObbA, comp1, LengthA);

	D3DXVECTOR2 LengthB = comp2->GetScale() * 0.5f;
	CreateObb(&ObbB, comp2, LengthB);

	return CheckObb(ObbA, ObbB);
}

void Intersect::CreateObb(ObbDesc * out, Rect * comp, D3DXVECTOR2 length)
{
	out->Position = comp->GetPosition() + comp->GetScale() * 0.5f;
	out->Length[0] = length.x;
	out->Length[1] = length.y;
	D3DXMATRIX World = comp->GetWorld();
	out->Direction[0] = D3DXVECTOR2(World._11, World._12);
	out->Direction[1] = D3DXVECTOR2(World._21, World._22);

	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);
}

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
