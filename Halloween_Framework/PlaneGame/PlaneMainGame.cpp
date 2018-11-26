#include "stdafx.h"
#include "PlaneMainGame.h"


PlaneMainGame::PlaneMainGame()
{
}


PlaneMainGame::~PlaneMainGame()
{
}

void PlaneMainGame::Init()
{
	player = NULL;
	enemy = NULL;
	miniMap = NULL;
	background = NULL;
	select.push_back(new AirPlane(L"Player.png"));
	select.push_back(new AirPlane2(L"SingleMario.png"));
	select.push_back(new AirPlane(L"Enemy.png"));

	for (int i = 0; i < select.size(); i++)
	{
		int padding = desc.Width / select.size();
		select[i]->Position(0, 0);
		select[i]->Update();
	}
	select[1]->GetSprite()->Scale(1, 1);
	select[1]->Position(2, -0.5f);

	bSelect = false;
	bHovering = false;
	image = NULL;

	transform = new Transform;
	transform->Scale(50, 100);

	for (int i = 0; i < 99; i++)
	{
		pChild[i] = new Transform;
		(i == 0) ? transform->AddChild(pChild[i]) 
			: pChild[i - 1]->AddChild(pChild[i]);

		pChild[i]->SetWorldPosition(120 + i * 120, 0);
	}

}
void PlaneMainGame::Release()
{
	for (int i = 0; i < select.size();i++)
	{
		SAFE_DELETE(select[i]);
	}
	for (int i = 0; i < 99; i++)
	{
		SAFE_DELETE(pChild[i]);
	}
	select.clear();
	SAFE_DELETE(enemy);
	SAFE_DELETE(background);
	SAFE_DELETE(miniMap);
	SAFE_DELETE(image);

	SAFE_DELETE(transform);
}
void PlaneMainGame::Update()
{
	select[0]->Update();
	transform->DefaultControl();
}
void PlaneMainGame::Render()
{
	select[0]->GetSprite()->World(transform->World());
	select[0]->Render();

	for (int i = 0; i < 99; i++)
	{
		select[1]->GetSprite()->World(pChild[i]->World());
		select[1]->Render();
	}
}

void PlaneMainGame::ShowInfo()
{
	if (bHovering)
	{
		ImGui::SetNextWindowPos(ImVec2(vMouse.x, desc.Height- vMouse.y));
		ImGui::SetNextWindowSize(ImVec2(400, 400));
		ImGui::Begin("Info", &bHovering);
		{
			ImGui::LabelText("", "Player%d", index);
			ImGui::LabelText("", "HP : %d", select[index]->GetHp());
			ImGui::LabelText("", "Damge : %d", 55);
		}
		ImGui::End();
	}
}
