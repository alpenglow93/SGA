#pragma once
class Math
{
public:
	Math();
	~Math();

	static D3DXVECTOR2 Vec2Cross(D3DXVECTOR2 v);
	static float Clamp(float value, float max, float min);
	static float Vec2Cross(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2);

};

