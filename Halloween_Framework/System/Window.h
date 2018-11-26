#pragma once
#include "MainGame.h"
#include "./Render/RenderTarget.h"
class Window
{
private:
	static LRESULT CALLBACK WndProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam
	);
	MainGame* mg;
	RenderTarget* target;
public:
	Window();
	~Window();

	WPARAM Run();
};

