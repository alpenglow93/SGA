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
