#include "stdafx.h"
#include "Intersect.h"


Intersect::Intersect()
{
}


Intersect::~Intersect()
{
}

float Intersect::GetAngle(Circle * comp1, Circle * comp2)
{
	D3DXVECTOR3 center1 = comp1->GetCenter();
	D3DXVECTOR3 center2 = comp2->GetCenter();

	D3DXVECTOR3 delta = center1 - center2;
	float distance = D3DXVec3Length(&delta);

	float angle = acosf(1 / distance);

	return angle;
}

bool Intersect::IsConstainRect(Rect * temp, Rect * comp1, Rect * comp2)
{
	bool isVertical = false;
	bool isHorizontal = false;
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	comp1->GetRect(&left1, &right1, &top1, &bottom1);
	comp2->GetRect(&left2, &right2, &top2, &bottom2);

	if (left1 <= right2 && right1 >= left2)
	{
		isHorizontal = true;
	}

	if (top1 >= bottom2 && bottom1 <= top2)
	{
		isVertical = true;
	}
	if (isHorizontal && isVertical)
	{
		return true;
	}

	return false;
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
		D3DXVECTOR3(left1, top1, 0),
		D3DXVECTOR3(right1, bottom1, 0)
	};
	D3DXVECTOR3 vec2[2] =
	{
		D3DXVECTOR3(left2, top2, 0),
		D3DXVECTOR3(right2, bottom2, 0)
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

	//sqrtf() 루트
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

bool Intersect::IsConstainsPoint(Rect * comp, D3DXMATRIX mat, D3DXVECTOR3 mouse)
{
	float left, top, right, bottom;
	comp->GetRect(&left, &right, &top, &bottom);

	D3DXVECTOR3 vec[2]
	{
		D3DXVECTOR3(left, bottom, 0),
		D3DXVECTOR3(right, top, 0)
	};
	D3DXVec3TransformCoord(&vec[0], &vec[0], &mat);
	D3DXVec3TransformCoord(&vec[1], &vec[1], &mat);

	bool bResult = true;
	//a = a + b -> a += b
	//a = a & b -> a &= b
	bResult &= vec[0].x < mouse.x;
	bResult &= vec[1].x > mouse.x;
	bResult &= vec[0].y < mouse.y;
	bResult &= vec[1].y > mouse.y;

	return bResult;
}
