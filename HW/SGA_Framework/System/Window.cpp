#include "stdafx.h"
#include "Window.h"
_D2DDesc desc;

LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}
	return DefWindowProc(handle, message, wParam, lParam);
}


Window::Window()
{
	//window 등록
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hInstance = desc.hInstance;
	wndClass.lpszClassName = desc.Appname.c_str();
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);

	assert(wHr != 0 && "Not RegisterClass");

	desc.Handle = CreateWindowEx(
		WS_EX_APPWINDOW,
		desc.Appname.c_str(),
		desc.Appname.c_str(),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		desc.hInstance,
		NULL
	);

	assert(desc.Handle != NULL && "Not CreateWindow");
	RECT rc = { 0, 0, (LONG)desc.Width, (LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	MoveWindow(
		desc.Handle,
		centerX, centerY,
		rc.right - rc.left,
		rc.bottom - rc.top,
		TRUE
	);

	ShowWindow(desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.Handle);
	SetFocus(desc.Handle);

}


Window::~Window()
{
	DestroyWindow(desc.Handle);

	UnregisterClass(desc.Appname.c_str(),
		desc.hInstance);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	//static int x = 100, y = 100;

	//HDC hdc = GetDC(desc.Handle);
	//HDC memDC = CreateCompatibleDC(hdc);
	//HBITMAP hBit;
	//hBit = (HBITMAP)CreateCompatibleBitmap(memDC, desc.Width, desc.Height);
	//HBITMAP hOBit = (HBITMAP)SelectObject(memDC, hBit);

	d2d = new D2D;

	//게임용 메세지 루프
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//게임동작
			//Update();
			//Render();

			////키입력
			//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			//{
			//	x -= 1;
			//	//InvalidateRect(desc.Handle, NULL, true);
			//}
			//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			//{
			//	x += 1;
			//	//InvalidateRect(desc.Handle, NULL, true);

			//}

			////랜더
			////백버퍼의 내용을 흰색으로
			//PatBlt(memDC, 0, 0, desc.Width, desc.Height, WHITENESS);
			////백버퍼에 내용을 그린다
			//Rectangle(memDC, x, y, x + 100, y + 100);
			////백버퍼의 내용을 전방버퍼로 보낸다
			//BitBlt(hdc, 0, 0, desc.Width, desc.Height, memDC, 0, 0, SRCCOPY);

			////HDC hdc = GetDC(desc.Handle);
			////Rectangle(hdc, x, y, x + 100, y + 100);
			////ReleaseDC(desc.Handle, hdc);

			d2d->Clear(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			{

			}
			d2d->Present();
		}
	}

	//ReleaseDC(desc.Handle, memDC);
	//ReleaseDC(desc.Handle, hdc);
	
	return msg.wParam;
}