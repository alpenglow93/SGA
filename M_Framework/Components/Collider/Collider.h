#pragma once
#include "../Component.h"
class Collider : public Component
{
public:
	Collider(class Object* obj);
	~Collider();

	void Update();
	void Render();

	void GetVertexAndWorld(Vertex** OutVertex,
		UINT& OutVertexCount, D3DXMATRIX& OutWorld);

	virtual bool IsOverlapWithMouse(class Camera* caemra) = 0; //∞„√∆¥¿≥ƒ?
protected:
	class Transform* transform;
	class ColorShader* matertial;

	Vertex* vertices;
	UINT vertexCount;
	ID3D11Buffer* vertexBuffer;

	D3DXMATRIX World;

	// Component¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void SetInsfector() override {};
};

