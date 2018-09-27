#include "stdafx.h"
#include "Intersect.h"


Intersect::Intersect()
{
}


Intersect::~Intersect()
{
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
