#pragma once
#include "./Mesh.h"
class Rhombus : public Mesh
{
public:
	Rhombus();
	~Rhombus();

	void Update() override;
	void Render() override;
};

