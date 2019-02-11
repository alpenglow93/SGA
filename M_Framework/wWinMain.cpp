#pragma once
#include "stdafx.h"
#include <time.h>
#include "./System/Window.h"
int WINAPI WinMain(
	HINSTANCE instance, //실질적 os
	HINSTANCE prevInstance, //지금은 사용 x 
	LPSTR param,
	int command
)
{
	srand((UINT)time(NULL));

	desc.AppName = L"D2D Game";
	desc.hInstance = instance;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 768;
	desc.bFullScreen = false;
	desc.bVsync = false;
	Window* window = new Window();
	WPARAM wParam = window->Run();
	delete window;

	return wParam;
}
