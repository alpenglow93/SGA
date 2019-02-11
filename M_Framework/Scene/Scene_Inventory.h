#pragma once
#include "./Scene.h"
class Scene_Inventory : public Scene
{
public:
	Scene_Inventory();
	~Scene_Inventory();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	class Camera* mainCameraComp;
	class QuadObject* quad;

	class Object* UIObject;
	class Camera* UICamera;
	
	class UITestPlayer* player;
};

