#pragma once
#include "Item.h"
__interface IUserInterface
{
public:
	virtual void Active() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual class Shader* GetMaterial(wstring name);
	virtual void SetCamera(class Camera* camera);


}; 

