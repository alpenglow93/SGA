#pragma once
#include "stdafx.h"
#include <time.h>
#include "./System/Window.h"
int WINAPI WinMain(
	HINSTANCE instance, //������ os
	HINSTANCE prevInstance, //������ ��� x 
	LPSTR param,
	int command
)
{
	srand(time(NULL));

	desc.AppName = L"D2D Game";
	desc.hInstance = instance;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;
	desc.bFullScreen = false;
	desc.bVsync = false;
	Window* window = new Window();
	WPARAM wParam = window->Run();
	delete window;

	return wParam;
}
