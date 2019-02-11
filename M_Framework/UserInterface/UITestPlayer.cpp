#include "stdafx.h"
#include "UITestPlayer.h"
#include "./Meshes/Circle.h"
#include "./Meshes/Rect.h"
#include "./Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Components/Animation/BoneClip.h"
#include "./Components/Collider/BoxCollider.h"
#include "./Components/Materials/TextureShader.h"
#include "./UserInterface/Status.h"
UITestPlayer::UITestPlayer()
{
	bone = new Object;
	circle = new Circle(100);
	bone->SetMesh(circle);
	root = bone->GetComponent<Transform>();
	root->SetWorldPosition(desc.Width / 2, 100);

	shader = Materials::Get()->Load<TextureShader>(L"Sprite.hlsl");

	for (int i = 0; i < 6; i++)
	{
		bones[i] = new Transform();

		//0 ¸öÅë 1¹ø ¸Ó¸® , 23, ¿Þ¿À ÆÈ , 45 ¿Þ¿À ´Ù¸® 
		(i == 0) ? bones[i]->AttachTo(root) : bones[i]->AttachTo(bones[0]);
		bones[i]->SetLocalPosition(0, 0);

		boneObj[i] = new Object;
		boneObj[i]->SetMesh(Meshes::Load<Rect>());
		boneObj[i]->GetComponent<Transform>()->AttachTo(bones[i]);
		collider[i] = new BoxCollider(boneObj[i]);
		boneObj[i]->PushComponent(collider[i]);
		boneObj[i]->GetComponent<Transform>()->SetLocalPosition(0,0);

	}

	bones[0]->SetLocalPosition(0, 350); //¸öÅë 450
	bones[1]->SetLocalPosition(0, 50); //¸Ó¸® 500
	
	bones[2]->SetLocalPosition(-100, -50); //¿ÞÆÈ 
	bones[3]->SetLocalPosition(100, -50); //¿À¸¥ÆÈ

	bones[4]->SetLocalPosition(-100, -250); //¿Þ´Ù¸®
	bones[5]->SetLocalPosition(100, -250); //¿À¸¥´Ù¸¥

	body = new QuadObject;
	head = new QuadObject;
	weapon = new QuadObject;

	body->SetMaterial(shader);
	head->SetMaterial(shader);
	weapon->SetMaterial(shader);
	
	body->GetComponent<Transform>()->AttachTo(bones[0]);
	body->GetComponent<Transform>()->SetLocalPosition(0,-100);
	body->GetComponent<Transform>()->Scale(1, 2);

	head->GetComponent<Transform>()->AttachTo(bones[1]);
	head->GetComponent<Transform>()->SetLocalPosition(0, 50);

	weapon->GetComponent<Transform>()->AttachTo(bones[3]);
	weapon->GetComponent<Transform>()->SetLocalPosition(50, -50);

	clip = new BoneClip;
}


UITestPlayer::~UITestPlayer()
{
	SAFE_DELETE(bone);
	for (int i = 0; i < 6; i++) {
		SAFE_DELETE(bones[i]);
		SAFE_DELETE(boneObj[i]);
	}
	SAFE_DELETE(body);
	SAFE_DELETE(head);
	SAFE_DELETE(weapon);
	SAFE_DELETE(clip);
}

void UITestPlayer::Update()
{
	root->DefaultControl();
	bone->Update();
	for (int i = 0; i < 6; i++)
	{
		bones[i]->Update();
		boneObj[i]->Update();


		if (collider[i]->IsOverlapWithMouse(camera))
		{
			if (Input->GetKey(VK_LBUTTON))
			{
				//ÀÌµ¿ È¸Àü
				//boneObj x; bones
				float angle = bones[i]->GetRotation();
				if(Input->GetKey('Q'))
					bones[i]->Rotation(angle + 90.0f * Time->Elapsed());
				if (Input->GetKey('E'))
					bones[i]->Rotation(angle - 90.0f * Time->Elapsed());
			
				//D3DXVECTOR2 position = bones[i]->GetWorldPosition();
				//int a = 0;
				bones[i]->SetWorldPosition(vMouse.x, vMouse.y);
			}
		}
	}

	body->Update();
	head->Update();
	weapon->Update();
	clip->Update();
}

void UITestPlayer::Render()
{
	bone->Render();
	for (int i = 0;i < 6;i++)
	{
		
		if (clip->GetFrame().size() > 0)
		{
			bones[i]->World(clip->GetFrame()[i]);
		}
		
		bones[i]->Render();
		circle->Render();
		boneObj[i]->Update();
		boneObj[i]->Render();
	}
	EquipItemRender(Status::Get()->GetBodyItem(), body);
	EquipItemRender(Status::Get()->GetHeadItem(), head);
	EquipItemRender(Status::Get()->GetWeaponItem(), weapon);

	ImGui::Begin("Insfactor");
	{
		if (ImGui::Button("Save"))
		{
			SaveFrame();
		}
		if (ImGui::Button("Play"))
		{
			clip->Play();
		}
	}
	ImGui::End();

}

void UITestPlayer::EquipItemRender(ItemInfo * item, QuadObject * obj)
{
	if (item->Type == ItemType::Empty) return;
	shader->Texture(item->Image);
	obj->Render();
}

void UITestPlayer::SaveFrame()
{
	Frame* frame = new Frame();
	frame->name = L"Frame_" + to_wstring(clip->GetFrameCount());
	frame->time = 0.3f;
	
	for (int i = 0; i < 6; i++)
	{
		FrameData* data = new FrameData(bones[i]->World());

		/*data->translation.x = bones[i]->GetLocalPosition().x;
		data->translation.y = bones[i]->GetLocalPosition().y;

		data->Rotation = bones[i]->GetWorldRotateQuaternion();
		data->scale.x = bones[i]->GetScale().x;
		data->scale.y = bones[i]->GetScale().y;*/


		frame->datas.push_back(data);
	}
	clip->AddFrameData(frame);



}
