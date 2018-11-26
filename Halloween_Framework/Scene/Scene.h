#pragma once
#include "./Singleton/SingletonBase.h"
#include "./Render/Shader.h"
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

/////////////////////////////////////////////////////////////////////////////

class Scenes : public SingletonBase<Scenes>
{
private:
	Scene * NowScene;
	Scene * ReleaseScene;

	map<wstring, Scene*> MapScene;

	Shader* shader;

	VertexPT* vertices;
	UINT vertexCount;

	ID3D11Buffer* vertexBuffer;
public:
	Scenes();
	~Scenes();

	void Update();
	void Render();

	void PostRender(ID3D11ShaderResourceView* SRV);

	void Add(wstring name, Scene* scene);
	void Change(wstring name);
private:
	void CreateVertexBuffer();

};

#define SCENES Scenes::Get()
