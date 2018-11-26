#include "stdafx.h"
#include "MainGame.h"
#include "./Utilities/Intersect.h"
#include "./Scene/TestScene.h"
#include "./PlaneGame/PlaneMainGame.h"
#include "./Render/RenderTarget.h"
MainGame::MainGame()
{

}

MainGame::~MainGame()
{

}

void MainGame::Init()
{
	SCENES->Add(L"PlaneGame", new PlaneMainGame);
	SCENES->Add(L"TestScene", new TestScene);
	SCENES->Change(L"PlaneGame");

	
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
	SCENES->Render();
}
void MainGame::Render()
{
	SCENES->Render();

	
	ImGui::Begin("MainWindow");
	{
		ImGui::Image(RenderTarget::Get()->Texture()
			, ImVec2(300, 300));
	}
	ImGui::End();



	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowSize(ImVec2(120, 20));
	ImGui::Begin("Info",(bool*)0, 
		ImGuiWindowFlags_NoTitleBar 
		//| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize);
	{
		ImGui::LabelText("", "FPS %.2f", ImGui::GetIO().Framerate);
	}
	ImGui::End();

}

void MainGame::PostRender()
{
	wstring str = L""
		L"DirectWrite Test\n"
		L"ÇÑ±Û Å×½ºÆ® \n"
		L"ùÛÙþ ¤¼¤¤¤±¤©\n"
		L"¡Ú¡Ù¡Ú\n"
		L"11525, afag";
	
	RECT rect = { 100,100, desc.Width, desc.Height };
	DirectWrite::RenderText(str, rect, 30, L"±Ã¼­Ã¼");
}

