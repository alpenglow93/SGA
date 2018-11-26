#pragma once
#include "Scene.h"
#include "./Animation/Animation.h"
class TestScene : public Scene
{
private:
	Animation* anim;
	Xml::XMLDocument* document;
public:
	TestScene();
	~TestScene();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void SaveClip(Xml::XMLNode* node, Clip* clip);
};

