#pragma once
#include "./Object/Rect.h"
#include "./Object/Circle.h"
class Intersect
{
public:
	Intersect();
	~Intersect();

	static float GetAngle(Circle* comp1, Circle* comp2);
	//return: 결과값
	//temp: 겹쳐진 부분
	//comp1: 사각형1
	//comp2: 사격형2
	static bool IsConstainRect(Rect* temp, Rect* comp1, Rect* comp2);
	static bool IsConstainRect(
		Rect* comp1, D3DXMATRIX mat1,
		Rect* comp2, D3DXMATRIX mat2);
	static bool IsConstainsCircle(Circle* comp1, Circle* comp2);
	static bool IsConstainsPoint(Circle* comp, D3DXVECTOR3 mouse);

	//return: 결과값
	//comp: rect 클래스
	//mat: 이동, 크기, 회전
	//mouse: 마우스 좌표
	static bool IsConstainsPoint(
		Rect* comp, D3DXMATRIX mat, D3DXVECTOR3 mouse
	);
};

