#include "stdafx.h"
#include "./System/Window.h"


LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);	//컴퓨터에게 0 이라는 메시지를 보냄
		//0 -> 메모리를 삭제하라
		//이걸 사용하지 않으면 창을 꺼도 프로세스에서 꺼지지 않음
		//프로세스에서 사용하고있기 때문에 껐다가 다시 켜는게 되지 않는다
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

Window::Window()
{
	//window 등록
	WNDCLASSEX wndClass;	//윈도우 구조체
	wndClass.cbClsExtra = 0;	//메모리 0으로
	wndClass.cbWndExtra = 0;	//메모리 0
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//브러쉬백그라운드. 창을 색칠하는것
	//창의 배경색을 흰색으로
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);	//winlogo: 기본 창모양 아이콘
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//hIconSm: 미리보기등에서 나오는 스몰아이콘
	wndClass.hInstance = desc.hInstance;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	//2byte
	WORD wHr = RegisterClassEx(&wndClass);

	//assert(조건)// 조건이 거짓일 경우 에러코드 생성
	//어느 파일에서 몇번째 줄, 조건의 내용으로
	assert(wHr != 0 && "Not RegisterClass");

	desc.Handle = CreateWindowEx(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(),	//클래스 이름(등록된 클래스 이름과 똑같아야함)
		desc.AppName.c_str(),	//타이틀 이름
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,	//창의 시작 가로 위치 100
		CW_USEDEFAULT,	//창의 시작 세로 위치 100
		CW_USEDEFAULT,	//창의 가로 크기 1280
		CW_USEDEFAULT,	//창의 세로 크기 768
		//CW_USEDEFAULT 기본값
		NULL,			//부모 윈도우
		(HMENU)NULL,	//메뉴
		desc.hInstance,
		NULL			//안 쓰는 녀석
	);

	assert(desc.Handle != NULL && "Not CreateWindow");
	RECT rc =
	{ 0, 0, (LONG)desc.Width, (LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	//SM_CXSCREEN: 모니터의 가로부분
	//모니터 가로에서 절반 부분을 빼주겠다
	UINT centerY = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Height) / 2;
	//창크기 재설정
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	//창이동
	MoveWindow(
		desc.Handle,
		centerX, centerY,
		rc.right - rc.left,
		rc.bottom - rc.top,
		TRUE
	);
	//창띄우기
	ShowWindow(desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.Handle);
	SetFocus(desc.Handle);
}


Window::~Window()
{
	DestroyWindow(desc.Handle);

	UnregisterClass(desc.AppName.c_str(),
		desc.hInstance);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	//게임용 메세지 루프
	while (GetMessage(&msg, desc.Handle,NULL, NULL))
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
			//실질적으로 게임 동작하는 구간
			//Update();
			//Render();
		}
	}
	return msg.wParam;
}
