#pragma once
#include "./Singleton/SingletonBase.h"
class Scene
{

public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void PreRender() = 0; //RTT 
	virtual void PostRender() =0; //2d

	void Render(); //
private:
	void CreateBlendState();

private:
	friend class Scenes;

	static class Object* rc; //화면 랜더용 
	static class Transform* rcTrans;
	static class PostEffect* shader;
	static class Object* collsionObj; //충돌 -> 카메라 기준 이동
	static class Transform* colliderTrans;//충돌체 이동용
	static class BoxCollider* collider; //충돌검사 
	
protected:
	class Object* mainCamera; //메인카메라 
	ID3D11BlendState* blendState[3]; //0 끄는 1 화면 + 텍스쳐 2텍스쳐 + 텍스쳐 
	
	vector<Object*> gameObjects;
	vector<Object*> renderObjects;
};
class Scenes : public SingletonBase<Scenes>
{
private:
	Scene * NowScene;
	Scene * ReleaseScene;

	map<wstring, Scene*> MapScene;
public:
	Scenes();
	~Scenes();

	void Update();
	void PreRender();
	void Render();
	void PostRender();

	void Add(wstring name, Scene* scene);
	void Change(wstring name);
};

#define SCENES Scenes::Get()
