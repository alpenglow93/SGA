#pragma once
#include "./Components/Materials/ColorShader.h"

using ObjFunction = void(class Object*);
class Object
{
protected:
	class Mesh* mesh;
	vector<Component*> Components;
	Material* material;
	bool bActive = false;
public:
	//Ȱ��ȭ ��Ȱ��ȭ �϶� ������ �ٸ��� ����
	ObjFunction* EnableActive; //false -> true;
	ObjFunction* DisableActive; //true -> false;
	ObjFunction* ActiveUpdate; //Active = ture ����
	ObjFunction* NotActiveUpdate; //Active = false
public:
	Object();
	virtual ~Object();

	void SetActive(bool active);
	virtual void Update();
	virtual void Render();

	void PushComponent(Component* comp);
	void SetMaterial(void* mat);
	void SetMesh(class Mesh* m) { mesh = m; }
	void ActiveSelf() { SetActive(!bActive); }

	bool GetActive() { return bActive; }
	Material* GetMaterial() { return material; }
	template<typename T>
	T* GetComponent()
	{
		T* result;
		for (Component* comp : Components)
		{
			result = dynamic_cast<T*>(comp);
			if (result != NULL) return result;
		}
		return NULL;
	}

	void Insfector();

};

