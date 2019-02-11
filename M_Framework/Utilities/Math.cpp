#include "stdafx.h"
#include "Math.h"


Math::Math()
{
}


Math::~Math()
{
}

D3DXVECTOR2 Math::Vec2Cross(D3DXVECTOR2 v)
{
	D3DXVECTOR3 vec1 = D3DXVECTOR3(v.x, v.y, 0.0f);
	D3DXVECTOR3 vec2 = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &vec1, &vec2);
	return D3DXVECTOR2(cross.x, cross.y);
}

float Math::Clamp(float value, float max, float min)
{
	if (value > max)
		return max;
	if (value < min)
		return min;

	return value;
}

float Math::Vec2Cross(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}
