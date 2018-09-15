#pragma once	//include를 한 헤더는 다시 읽지 않겠다
#include "stdafx.h"
#include "./System/Window.h"

//WinMain: 진입점
int WINAPI WinMain(
	HINSTANCE instance,		//실질적인 os버전
	HINSTANCE precInstance,	//지금은 사용하지 않음
	LPSTR param,
	int command
)
{
	desc.AppName = L"D2D Game";		//유니코드로 사용할땐 "" 앞에 L을 붙여줘야한다
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