#pragma once
#include "./Mesh.h"
class Rect : public Mesh
{
public:
	Rect();
	~Rect();

	void Update();
	void Render();
};

