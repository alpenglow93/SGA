#pragma once
#include "Item.h"
class UITestPlayer
{
public:
	UITestPlayer();
	~UITestPlayer();

	void Update();
	void Render();

	void SetCamera(class Camera* cam) { camera = cam; }

private:
	void EquipItemRender(ItemInfo* item, class QuadObject* obj);

	void SaveFrame();

private:
	class Object* bone; //������Ʈ�� ��ġ 
	class Circle* circle; 
	class Transform* root; // ������ 

	class Object* boneObj[6];
	class BoxCollider* collider[6];
	class Transform* bones[6]; //�̹��� ��� ��ġ 
	class TextureShader* shader;

	class QuadObject* body;
	class QuadObject* head;
	class QuadObject* weapon;

	class Camera* camera;

	class BoneClip* clip;
};

