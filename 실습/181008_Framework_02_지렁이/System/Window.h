#pragma once
//#include "D2D.h"
#include "MainGame.h"
class Window
{
private:
	static LRESULT CALLBACK WndProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam
	);

	//D2D* d2d;
	MainGame* mg;
public:
	Window();
	~Window();

	WPARAM Run();
};

