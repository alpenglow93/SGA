#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

void TestScene::Init()
{

	anim = new Animation;
	document = new Xml::XMLDocument();
	Xml::XMLNode* root = document->NewElement("Root");
	document->InsertFirstChild(root);

	Xml::XMLElement* element = document->NewElement("Idle");
	element->Attribute("ChildCont", "3");
	root->InsertEndChild(element);

	Clip* clip = new Clip();
	clip->AddFrame(new Sprite(L"Metalslug.png", 4, 2, 34, 40), 0.3f);
	clip->AddFrame(new Sprite(L"Metalslug.png", 35, 2, 64, 40), 0.3f);
	clip->AddFrame(new Sprite(L"Metalslug.png", 64, 2, 97, 40), 0.3f);
	
	this->SaveClip(element, clip);
	document->SaveFile("Idle.xml");

	anim->AddClip(L"Idle", clip);

}

void TestScene::Release()
{
	SAFE_DELETE(anim);
}

void TestScene::Update()
{
	//AnimationContoroller ->
	if (Input->GetKeyDown('1'))
	{
		anim->Play(L"Idle");
	}
	//anim->Update();
	if (Input->GetKeyDown(VK_RETURN))
	{
		SCENES->Change(L"PlaneGame");
	}
}

void TestScene::Render()
{
	//anim->Render();
}

void TestScene::SaveClip(Xml::XMLNode * node, Clip * clip)
{
	for (int i = 0; i < 3; i++)
	{
		char str[32];
		printf_s(str, "Frame%d", i);
		Xml::XMLElement* element = document->NewElement(str);
		node->InsertEndChild(element);

		Xml::XMLElement* fileName = document->NewElement("File");
		fileName->SetText("");
		element->InsertEndChild(fileName);

		Xml::XMLElement* Start = document->NewElement("Texture");
		element->InsertEndChild(Start);

		printf_s(str, "%d, %d, %d, %d", 0, 0, 0, 0);
		Start->Attribute("Rect", str);

		Xml::XMLElement* Time = document->NewElement("Time");
		Time->SetText(0.0f);
		element->InsertEndChild(Time);

	}
	
}
