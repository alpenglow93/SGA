#pragma once
#include "Rect.h"
class Intersect
{
public:
	Intersect();
	~Intersect();

	//return: �����
	//temp: ������ �κ�
	//comp1: �簢��1
	//comp2: �����2
	static bool IsConstainRect(Rect* temp, Rect* comp1, Rect* comp2);
	static bool IsConstainRect(
		Rect* comp1, D3DXMATRIX mat1,
		Rect* comp2, D3DXMATRIX mat2);

	//return: �����
	//comp: rect Ŭ����
	//mat: �̵�, ũ��, ȸ��
	//mouse: ���콺 ��ǥ
	static bool IsConstainsPoint(
		Rect* comp, D3DXMATRIX mat, D3DXVECTOR3 mouse
	);
};

