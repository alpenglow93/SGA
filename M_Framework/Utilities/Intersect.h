#pragma once


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
	static float GetAngle(class SphereCollider* comp1,
		class SphereCollider* comp2);
	
	
	static bool IsConstainsRect(
		class BoxCollider* comp1, 
		class BoxCollider* comp2);
	
	static bool IsConstainsCircle(class SphereCollider* comp1, class SphereCollider* comp2);
	static bool IsConstainsPoint(class SphereCollider* comp1, D3DXVECTOR3 pos);
	//static bool IsConstainsPoint(Rect* comp, D3DXVECTOR3 mouse);

	//static bool IsOBB(Rect* comp1, Rect* comp2);
private:
	//static void CreateObb(ObbDesc* out, Rect* comp, D3DXVECTOR2 length);
	static float SeparateAxis(D3DXVECTOR2 &separate, D3DXVECTOR2& e1, D3DXVECTOR2& e2);
	static bool CheckObb(ObbDesc& obbA, ObbDesc& obbB);
};

