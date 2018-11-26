#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

//////////////////////////////////////////////////////////////////////////

Scenes::Scenes()
	: NowScene(NULL), ReleaseScene(NULL)
{
}

Scenes::~Scenes()
{
	if (NowScene != NULL)
		NowScene->Release();
	if (ReleaseScene != NULL)
		ReleaseScene->Release();

	for (auto scene : MapScene)
	{
		SAFE_DELETE(scene.second);
	}
}

void Scenes::Update()
{
	if (NowScene != NULL)
		NowScene->Update();

	if (ReleaseScene != NULL)
	{
		ReleaseScene->Release();
		ReleaseScene = NULL;
	}
}

void Scenes::Render()
{
	if (NowScene != NULL)
		NowScene->Render();
}

void Scenes::Add(wstring name, Scene * scene)
{
	if (MapScene.count(name) > 0)
	{
		wstring error = name + L" Scene name alreay Add map";
		MessageBox(NULL, error.c_str(), L"Scene Add Error", MB_OK);
		return;
	}

	MapScene[name] = scene;
}

void Scenes::Change(wstring name)
{
	auto iter = MapScene.find(name);
	if (iter == MapScene.end()) return;
	if (iter->second == NowScene) return;
	
	if (NowScene == NULL)
	{
		NowScene = iter->second;
		NowScene->Init();
	}
	else
	{
		ReleaseScene = NowScene;
		NowScene = iter->second;
		NowScene->Init();
	}
}
