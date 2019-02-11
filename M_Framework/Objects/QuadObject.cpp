#include "stdafx.h"
#include "QuadObject.h"
#include "./Meshes/Rect.h"
#include "./Components/Collider/BoxCollider.h"
QuadObject::QuadObject()
{
	mesh = Meshes::Load<Rect>();
	BoxCollider* collider = new BoxCollider(this);
	Components.push_back(collider);
}


QuadObject::~QuadObject()
{
}
