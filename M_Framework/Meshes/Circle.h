#pragma once
#include "./Mesh.h"
#define CIRCLESEGMENTS 36
class Circle : public Mesh
{
public:
	Circle(float radius = 50);
	~Circle();

	void Update();
	void Render();

	D3DXVECTOR3 GetCenter() { return Center; }
	float GetRadius() { return Radius; }

private:
	D3DXVECTOR3 Center;
	float Radius;

	D3DXVECTOR3 position[CIRCLESEGMENTS + 1]; //반지름 미적용 원
};