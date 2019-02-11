#pragma once
#include "Scene.h"
#include <thread>
class Scene_FrustumCulling : public Scene
{

public:
	Scene_FrustumCulling();
	~Scene_FrustumCulling();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

	void EA();
	void DA();
	void AU();
	void DU();
	static int currentBulletCount;

private:
	static float respwanTime;
	static float maxHp;
	static float currentHp;

	int maxBulletCount = 10;

	bool bReload = false;
	thread* th1;

	class PrograssBar* bar;
	float curGauge;
	class Ray* ray;
	class SphereCollider* collider;
	class SphereCollider* check;
	class SphereCollider* check2;
	class BoxCollider* boxCollider;


};

