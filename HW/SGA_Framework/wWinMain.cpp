#pragma once
#include "stdafx.h"
#include "./System/Window.h"

int WINAPI WinMain(
	HINSTANCE instance,
	HINSTANCE PrevInstance,
	LPSTR param,
	int command
)
{
	desc.Appname = L"D2D Game";
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