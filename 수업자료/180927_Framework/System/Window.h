#pragma once
#include "MainGame.h"
class Window
{
private:
	static LRESULT CALLBACK WndProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam
	);
	MainGame* mg;
public:
	Window();
	~Window();

	WPARAM Run();
};

