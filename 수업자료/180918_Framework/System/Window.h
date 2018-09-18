#pragma once
#include "D2D.h"
class Window
{
private:
	static LRESULT CALLBACK WndProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam
	);

	D2D* d2d;
public:
	Window();
	~Window();

	WPARAM Run();
};

