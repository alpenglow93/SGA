#pragma once

//Ray -> 반직선

class Ray
{
public:
	Ray();
	Ray(D3DXVECTOR2& origin, D3DXVECTOR2& direction);
	~Ray();

	void Initialize();

	void Update();
	void Render();

	void SetOrigin(float x, float y);		//시작점 셋팅
	void SetDirection(float x, float y);	//방향 셋팅
	void SetTarget(float x, float y);		//특정 대상으로

	class Transform* GetTransform() { return transform; }
	bool Raycast(class SphereCollider* collider,D3DXVECTOR2* point = NULL, D3DXVECTOR2* normal= NULL);
	bool Raycast(class BoxCollider* collider, D3DXVECTOR2* point = NULL, D3DXVECTOR2* normal = NULL);
private:
	D3DXVECTOR2 Origin;		//시작점
	D3DXVECTOR2 Direction;	//방향

	ID3D11Buffer* buffer;
	class ColorShader* shader;
	class Transform* transform;
};

