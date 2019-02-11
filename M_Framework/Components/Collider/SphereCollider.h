#pragma once
#include "Collider.h"
class SphereCollider : public Collider 
{
public:
	SphereCollider(class Object* obj);
	~SphereCollider();

	void Update();
	void Render();

	void SetCenter(float x, float y);
	void SetRadius(float r);

	void GetWorldCenterRadius(OUT D3DXVECTOR2* center, OUT float* radius);
	// Collider��(��) ���� ��ӵ�
	virtual bool IsOverlapWithMouse(Camera * caemra) override;
private:
	D3DXVECTOR2 Center;
	float Radius;
};

