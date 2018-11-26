#pragma once
#include "./Object/Rect.h"
#include "./Object/Circle.h"

struct ObbDesc
{
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Direction[2];
	float Length[2];
};

class Intersect
{
public:
	Intersect();
	~Intersect();

	static float GetAngle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);
	static float GetAngle(Circle* comp1, Circle* comp2);
	//return : 결과값
	//temp : 겹쳐진 부분
	//comp1 : 사각형 1
	//comp2 : 사각형 2
	static bool IsConstainRect(Rect* temp, Rect* comp1, Rect* comp2);
	static bool IsConstainRect(Rect* comp1, D3DXMATRIX mat1,Rect* comp2, D3DXMATRIX mat2);
	static bool IsConstainsCircle(Circle* comp1, Circle* comp2);
	static bool IsConstainsPoint(Circle* comp2, D3DXVECTOR3 mouse);
	static bool IsConstainsPoint(Rect* comp, D3DXVECTOR3 mouse);



	static bool IsOBB(Rect* comp1, Rect* comp2);
private:
	static void CreateObb(ObbDesc* out, Rect* comp, D3DXVECTOR2 length);
	static float SeparateAxis(D3DXVECTOR2 &separate, D3DXVECTOR2& e1, D3DXVECTOR2& e2);
	static bool CheckObb(ObbDesc& obbA, ObbDesc& obbB);
};

