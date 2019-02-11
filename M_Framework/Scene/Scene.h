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

	static class Object* rc; //ȭ�� ������ 
	static class Transform* rcTrans;
	static class PostEffect* shader;
	static class Object* collsionObj; //�浹 -> ī�޶� ���� �̵�
	static class Transform* colliderTrans;//�浹ü �̵���
	static class BoxCollider* collider; //�浹�˻� 
	
protected:
	class Object* mainCamera; //����ī�޶� 
	ID3D11BlendState* blendState[3]; //0 ���� 1 ȭ�� + �ؽ��� 2�ؽ��� + �ؽ��� 
	
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
