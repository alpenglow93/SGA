#pragma once	//include�� �� ����� �ٽ� ���� �ʰڴ�
#include "stdafx.h"
#include "./System/Window.h"

//WinMain: ������
int WINAPI WinMain(
	HINSTANCE instance,		//�������� os����
	HINSTANCE precInstance,	//������ ������� ����
	LPSTR param,
	int command
)
{
	desc.AppName = L"D2D Game";		//�����ڵ�� ����Ҷ� "" �տ� L�� �ٿ�����Ѵ�
	desc.hInstance = instance;
	desc.bFullScreen = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;

	Window* window = new Window();
	WPARAM wParam = window->Run();
	delete window;

	return wParam;
}