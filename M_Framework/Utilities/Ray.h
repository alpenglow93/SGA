#pragma once

//Ray -> ������

class Ray
{
public:
	Ray();
	Ray(D3DXVECTOR2& origin, D3DXVECTOR2& direction);
	~Ray();

	void Initialize();

	void Update();
	void Render();

	void SetOrigin(float x, float y);		//������ ����
	void SetDirection(float x, float y);	//���� ����
	void SetTarget(float x, float y);		//Ư�� �������

	class Transform* GetTransform() { return transform; }
	bool Raycast(class SphereCollider* collider,D3DXVECTOR2* point = NULL, D3DXVECTOR2* normal= NULL);
	bool Raycast(class BoxCollider* collider, D3DXVECTOR2* point = NULL, D3DXVECTOR2* normal = NULL);
private:
	D3DXVECTOR2 Origin;		//������
	D3DXVECTOR2 Direction;	//����

	ID3D11Buffer* buffer;
	class ColorShader* shader;
	class Transform* transform;
};

