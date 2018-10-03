#pragma once
#include "stdafx.h"
#include "./System/Window.h"
int WINAPI WinMain(
	HINSTANCE instance,
	HINSTANCE prevInstance,
	LPSTR param,
	int command
)
{
	//랜더링 파이프 라인?
	//직선을 랜더해야 된다.

	//로컬 -> 도형이나 선의 모양
	//월드 -> 특정 공간의 위치, 회전, 크기
	//뷰 -> 카메라
	//투영 -> 직교 투영(2D), 원근 투영(3D)
	//뷰포트 -> 창의 크기

	desc.AppName = L"D2D Game";
	desc.hInstance = instance;
	desc.bFullScreen = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;

	Window* window = new Window();

	//HDC hdc = GetDC(desc.Handle);
	//Rectangle(hdc, 100, 100, 200, 200);
	//ReleaseDC(desc.Handle, hdc);

	WPARAM wParam = window->Run();
	delete window;

	return wParam;
}