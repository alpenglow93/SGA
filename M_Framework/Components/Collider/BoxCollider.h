#pragma once
#include "./Collider.h"
class BoxCollider : public Collider
{
public:
	BoxCollider(class Object* obj);
	~BoxCollider();

	void Update();
	void Render();


	void Center(float x, float y);
	void Size(float x, float y);

	virtual bool IsOverlapWithMouse(class Camera* caemra) override;
	virtual void SetInsfector() override;

	void GetWorldVertices(D3DXVECTOR2* vertex, D3DXVECTOR2* center);
private:
	D3DXVECTOR2 center;
	D3DXVECTOR2 size;
	D3DXVECTOR3 mouse;
	D3DXVECTOR3 dir;
	D3DXVECTOR3* ctrolp;
};

