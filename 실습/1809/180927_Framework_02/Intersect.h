#pragma once
#include "Rect.h"
class Intersect
{
public:
	Intersect();
	~Intersect();

	//return: 결과값
	//temp: 겹쳐진 부분
	//comp1: 사각형1
	//comp2: 사격형2
	static bool IsConstainRect(Rect* temp, Rect* comp1, Rect* comp2);
	static bool IsConstainRect(
		Rect* comp1, D3DXMATRIX mat1,
		Rect* comp2, D3DXMATRIX mat2);
};

