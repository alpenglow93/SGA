#include "stdafx.h"
#include "Scene.h"
#include "./Components/Materials/Material.h"
#include "./Components/Materials/ColorShader.h"
#include "./Components/Materials/TextureShader.h"
#include "./Components/Materials/PostEffect.h"
#include "./Components/Collider/BoxCollider.h"
#include "./Components/Transform.h"
#include "./Components/Camera.h"
#include "./Meshes/Rect.h"
#include "./Objects/Object.h"
#include "./Utilities/Intersect.h"

Object* Scene::rc = NULL;
Object* Scene::collsionObj = NULL;

Transform* Scene::rcTrans = NULL;
Transform* Scene::colliderTrans = NULL;

BoxCollider* Scene::collider = NULL;
PostEffect* Scene::shader = NULL;

Scene::Scene()
{
	CreateBlendState();
	Materials::Get()->Load<ColorShader>(L"Effect.hlsl");
	Materials::Get()->Load<TextureShader>(L"Sprite.hlsl");

	mainCamera = new Object; //빈오브젝트
	mainCamera->SetActive(true);
	mainCamera->PushComponent(new Camera(mainCamera));
}

Scene::~Scene()
{
	SAFE_DELETE(mainCamera);
}


void Scene::Render()
{
	shader->Texture(RenderTarget::Get()->Texture());
	rc->Render();
}

void Scene::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = { 0 };

	blendDesc.RenderTarget[0].BlendEnable = false;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	DEVICE()->CreateBlendState(&blendDesc, &blendState[0]);

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	DEVICE()->CreateBlendState(&blendDesc, &blendState[1]);

	blendDesc.RenderTarget->SrcBlendAlpha = D3D11_BLEND_ONE;
	DEVICE()->CreateBlendState(&blendDesc, &blendState[2]);
}
/////////////////////////////////////////////////////////////


Scenes::Scenes()
	: NowScene(NULL), ReleaseScene(NULL)
{
	Scene::rc = new Object;
	Scene::rc->SetMesh(Meshes::Load<Rect>());
	Scene::rc->SetActive(true);

	Scene::rcTrans = Scene::rc->GetComponent<Transform>();
	Scene::rcTrans->Scale(0.02f, 0.02f);	
	Scene::rcTrans->SetWorldPosition(0, -0.05f);
	Scene::shader = Materials::Get()->Load<PostEffect>(L"PostEffect.hlsl");
	Scene::rc->SetMaterial(Scene::shader);

	Scene::collsionObj = new Object;
	Scene::collsionObj->SetActive(true);

	Scene::colliderTrans = Scene::collsionObj->GetComponent<Transform>();
	Scene::collider = new BoxCollider(Scene::collsionObj);
	Scene::collsionObj->PushComponent(Scene::collider);

	Scene::collider->Size(desc.Width / 100.0f, desc.Height / 100.0f);
	Scene::collider->Center(desc.Width / 2, desc.Height / 2);
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
	SAFE_DELETE(Scene::rc);
	SAFE_DELETE(Scene::collsionObj);
}


void Scenes::Update()
{
	if (NowScene != NULL)
	{
		NowScene->mainCamera->Update();
		NowScene->Update();
		Scene::colliderTrans->SetWorldPosition(
			NowScene->mainCamera->GetComponent<Transform>()->
			GetWorldPosition());
		Scene::collsionObj->Update();
		NowScene->renderObjects.clear();
		for (int i = 0; i < NowScene->gameObjects.size(); i++)
		{
			//1. 업데이트는 모두 동작하면서 랜더만
			NowScene->gameObjects[i]->Update();
			//_.랜더될 대상들은 무조건 Collider가 있어야 되고
			//2_boxCollider 충돌이기 때문에
			//2_SphereCollider를 가지고 있으면 랜더가 안된다.
			if (Intersect::IsConstainsRect(
				NowScene->gameObjects[i]->GetComponent<BoxCollider>(),
				Scene::collider))
			{
				NowScene->renderObjects.push_back(
					NowScene->gameObjects[i]);
			}
			//2. 업데이트 랜더 모두 
		}

		//충돌 대상은 카메라 , object
	}
	if (ReleaseScene != NULL)
	{
		ReleaseScene->Release();
		ReleaseScene = NULL;
	}
}

void Scenes::PreRender()
{
	if (NowScene != NULL)
	{
		//DEVICECONTEXT()->OMSetBlendState(NowScene->blendState[1], NULL, 0xFF);
		NowScene->mainCamera->Render();
		NowScene->PreRender();
		for (int i = 0; i < NowScene->renderObjects.size(); i++)
		{
			NowScene->renderObjects[i]->Render();
		}
		//DEVICECONTEXT()->OMSetBlendState(NowScene->blendState[0], NULL, 0xFF);
	}
}

void Scenes::Render()
{
	if (NowScene != NULL)
	{ 
		D3DXMATRIX idx; 
		D3DXMatrixIdentity(&idx);
		//NowScene->mainCamera->GetComponent<Camera>()->SetViewOrhto(&idx, &idx);
		NowScene->Render();
	}
}

void Scenes::PostRender()
{
	if (NowScene != NULL) { NowScene->PostRender(); }
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

