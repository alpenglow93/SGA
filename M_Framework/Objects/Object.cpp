#include "stdafx.h"
#include "Object.h"
#include "Components/Transform.h"
#include "Meshes/Mesh.h"
Object::Object()
	: EnableActive(NULL), DisableActive(NULL),
	ActiveUpdate(NULL), NotActiveUpdate(NULL)
{

	mesh = NULL;
	Components.push_back(new Transform);
	material = new ColorShader(L"Effect.hlsl");
}


Object::~Object()
{
	for (Component* comp : Components)
		SAFE_DELETE(comp);
}

void Object::SetActive(bool active)//false->true, true->false
{
	if (bActive && !active) //활성->비활성
	{
		if(DisableActive != NULL)
			DisableActive(this);
	}
	if (!bActive && active) //비활성->활성화
	{
		if (EnableActive != NULL)
			EnableActive(this);
	}
	bActive = active;
}

void Object::Update()
{
	if (bActive == true)
	{
		if (ActiveUpdate != NULL)
			ActiveUpdate(this);

		for (Component* comp : Components)
			comp->Update();
		material->Update();
	}
	else
	{
		if (NotActiveUpdate != NULL)
			NotActiveUpdate(this);
	}
}

void Object::Render()
{
	if (bActive == true)
	{
		Transform* transform = GetComponent<Transform>();

	#ifdef _DEBUG
		for (Component* comp : Components)
			comp->Render();
	#endif // _DEBUG

		material->World(transform->World());
		material->Render();
		if (mesh != NULL)
			mesh->Render();
	}
}

void Object::PushComponent(Component * comp)
{
	Components.push_back(comp);
}

void Object::SetMaterial(void* mat)
{
	material = (Material*)mat;
}


void Object::Insfector()
{
	if (bInsfacter)
	{
		if (ImGui::Begin("Insfactor", &bInsfacter))
		{
			for (Component* comp : Components)
				comp->SetInsfector();

			material->SetInsfector();

			ImGui::End();
		}
	}
	
}

