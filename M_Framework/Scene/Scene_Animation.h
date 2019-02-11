#pragma once
#include "Scene.h"
class Scene_Animation : public Scene
{
public:
	Scene_Animation();
	~Scene_Animation();
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	class QuadObject* quad;
	class Animation* anim;
};

