#pragma once
#include "./Object/Rect.h"
#include "./Object/Circle.h"
class Intersect
{
public:
	Intersect();
	~Intersect();

	static float GetAngle(Circle* comp1, Circle* comp2);
	//return: �����
	//temp: ������ �κ�
	//comp1: �簢��1
	//comp2: �����2
	static bool IsConstainRect(Rect* temp, Rect* comp1, Rect* comp2);
	static bool IsConstainRect(
		Rect* comp1, D3DXMATRIX mat1,
		Rect* comp2, D3DXMATRIX mat2);
	static bool IsConstainsCircle(Circle* comp1, Circle* comp2);
	static bool IsConstainsPoint(Circle* comp, D3DXVECTOR3 mouse);

	//return: �����
	//comp: rect Ŭ����
	//mat: �̵�, ũ��, ȸ��
	//mouse: ���콺 ��ǥ
	static bool IsConstainsPoint(
		Rect* comp, D3DXMATRIX mat, D3DXVECTOR3 mouse
	);
};

