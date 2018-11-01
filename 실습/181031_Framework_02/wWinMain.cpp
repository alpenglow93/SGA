#pragma once
#include "stdafx.h"
#include <time.h>
#include "./System/Window.h"
int WINAPI WinMain(
	HINSTANCE instance,	//실질적 os
	HINSTANCE prevInstance,	//지금은 사용 x
	LPSTR param,
	int command
)
{
	srand(time(NULL));

	desc.AppName = L"D2D Game";
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