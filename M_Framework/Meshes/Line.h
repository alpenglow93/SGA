#pragma once
#include "./Mesh.h"
class Line : public Mesh
{
public:
	Line();
	~Line();

	void Update() override;
	void Render() override;

	void Direction(float x, float y, class Transform* trans);
	void Direction(D3DXVECTOR2 vec, class Transform* trans);

};

