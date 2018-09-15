#pragma once
class Window
{
private:
	static LRESULT CALLBACK WndProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam
	);

public:
	Window();
	~Window();

	WPARAM Run();
};

