#include "stdafx.h"
#include "MainGame.h"
#include "./Scene/Scene_Inventory.h"
#include "./Scene/Scene_Animation.h"
#include "./Scene/Scene_FrustumCulling.h"
#include "./MapleStory/TestScene.h"

bool bInsfacter;
bool bWorldOutlinear;
MainGame::MainGame()
{
	bInsfacter = true;
	bMainWindow = true;
	bWorldOutlinear = true;
}

MainGame::~MainGame()
{

}

void MainGame::Init()
{
	SCENES->Add(L"Test", new Scene_Animation);
	SCENES->Change(L"Test");
}
void MainGame::Release()
{
	SCENES->Delete();
}
void MainGame::Update()
{
	SCENES->Update();
}
void MainGame::PreRender()
{
	SCENES->PreRender();
}
void MainGame::Render()
{
	SCENES->Render();
	MainMenuBarSetting();
	ShowInsfacter();
}
void MainGame::PostRender()
{
	SCENES->PostRender();
}

void MainGame::MainMenuBarSetting()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Windows"))
		{
			ImGui::MenuItem("Insfacter", "Ctrl + 2", &bInsfacter);
			ImGui::MenuItem("OutLinear", "Ctrl + 3", &bWorldOutlinear);

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void MainGame::ShowInsfacter()
{


	if (Input->GetKey(VK_LCONTROL))
	{
		if (Input->GetKeyDown('2')) bInsfacter = !bInsfacter;
		if (Input->GetKeyDown('3')) bWorldOutlinear = !bWorldOutlinear;
	}

	ImGui::SetNextWindowSize(ImVec2(250, desc.Height));
	ImGui::SetNextWindowPos(ImVec2(desc.Width, 18));

	if (bInsfacter)
	{
		if (ImGui::Begin("Insfactor", &bInsfacter,
			ImGuiWindowFlags_AlwaysHorizontalScrollbar
			| ImGuiWindowFlags_NoMove))
		{

			ImGui::End();
		}
	}
	ImGui::SetNextWindowSize(ImVec2(250, 150));
	ImGui::SetNextWindowPos(ImVec2(desc.Width, desc.Height));
	if (bWorldOutlinear)
	{
		if (ImGui::Begin("WorldOutlinear", &bWorldOutlinear,
			ImGuiWindowFlags_AlwaysHorizontalScrollbar
			| ImGuiWindowFlags_NoMove))
		{

			ImGui::End();
		}
	}

	ImGui::SetNextWindowSize(ImVec2(60, 20));
	ImGui::SetNextWindowPos(ImVec2(0, 18));
	ImGui::Begin("Info", (bool*)1, ImGuiWindowFlags_NoTitleBar);
	{
		ImGui::LabelText("", "FPS : %0.2f", ImGui::GetIO().Framerate);
	}
	ImGui::End();
}

