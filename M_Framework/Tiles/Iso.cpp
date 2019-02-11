#include "stdafx.h"
#include "Iso.h"
#include "Objects/Object.h"
#include "./Meshes/Rhombus.h"
#include "Components/Transform.h"
#include "Components/Materials/SplatShader.h"

Iso::Iso()
{
	obj = new Object;
	obj->SetMesh(Meshes::Load<Rhombus>());
	Transform* trans = obj->GetComponent<Transform>();
	trans->SetWorldPosition(desc.Width / 2, desc.Height / 2);
	trans->Scale(7, 7);

	SplatShader* shader = Materials::Get()->Load<SplatShader>(L"Splat.hlsl");
	ID3D11ShaderResourceView* control = Sprites::Load(_Texture + L"terrainControl2.jpg");
	ID3D11ShaderResourceView* tiles[4];
	tiles[0] = Sprites::Load(_Texture + L"Tile0.jpg");
	tiles[1] = Sprites::Load(_Texture + L"Tile1.jpg");
	tiles[2] = Sprites::Load(_Texture + L"Tile2.jpg");
	tiles[3] = Sprites::Load(_Texture + L"Tile3.jpg");
	shader->Texture(control, tiles);
	obj->SetMaterial(shader);
}


Iso::~Iso()
{
	SAFE_DELETE(obj);
}

void Iso::Update()
{
	obj->Update();
}

void Iso::Render()
{
	obj->Render();
	obj->Insfector();
}
