#include "stdafx.h"
#include "Window.h"
_D2DDesc desc;
D3DXVECTOR3 vMouse;
Timer* Time;
LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc((UINT*)handle, message, wParam, lParam))
		return true;

	if (message == WM_MOUSEWHEEL)
	{
		if ((SHORT)HIWORD(wParam) > 0)
		{
			vMouse.z += 1.0f;
		}
		else
		{
			vMouse.z -= 1.0f;
		}
	}
	else if (message == WM_MOUSEMOVE)
	{
		vMouse.x = (float)LOWORD(lParam);
		vMouse.y = desc.Height - (float)HIWORD(lParam);
		vMouse.y += 15.0f;
	}
	else if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}
	return DefWindowProc(handle,message,wParam,lParam);
}

Window::Window()
{
	//window 등록 
	WNDCLASSEX wndClass; //윈도우 구조체 
	wndClass.cbClsExtra = 0; //메모리 그냥 0
	wndClass.cbWndExtra = 0; //메모리 그냥 0
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //창의 배경색은 흰색
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hInstance = desc.hInstance;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	//2byte 
	WORD wHr = RegisterClassEx(&wndClass);

	//assert(조건)// 조건이 거짓 에러 코드생성 
	//어느 파일에서 몇번째 줄, 조건의 내용으로 
	assert(wHr != 0 && "Not RegisterClass");

	desc.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(), // 클래스 이름(등록된 클래스 이름과 무조건 같아야 됌)
		desc.AppName.c_str(), // 타이틀 이름,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // 창의 시작위치 가로 100
		CW_USEDEFAULT, // 창의 시작 세로 위치 100
		CW_USEDEFAULT, // 창의 가로 크기 1280
		CW_USEDEFAULT, // 창의 세로 크기 768
		NULL,			//부모 윈도우 
		(HMENU)NULL,	//메뉴
		desc.hInstance,	
		NULL			//안쓰는 녀석 
	);

	assert(desc.Handle != NULL && "Not CreateWindow");
	RECT rc = 
	{ 0,0,(LONG)desc.Width +250,(LONG)desc.Height + 150 };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.Height) / 2;
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

	D2DCLASS();

	ImGui::Create(desc.Handle, DEVICE(), DEVICECONTEXT());
	ImGui::StyleColorsDark();

	Time = new Timer;
	mg = new MainGame;
	mg->Init();

	DirectWrite::Get();

	RenderTarget::Get(desc.Width, desc.Height);
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
			//Updates
			{
				Time->Update();
				SOUND->Update();
				mg->Update();
				ImGui::Update();
			}
			RenderTarget::Get()->Clear(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
			{
				mg->PreRender();
				if (Input->GetKey(VK_LCONTROL))
				{
					if (Input->GetKeyDown(VK_F1))
					{
						RenderTarget::Get()->SaveFile(L"Rtt_Test.png");
					}
				}
			}
			
			//Renders
			D2DCLASS()->Clear(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			{
				mg->Render();
				DirectWrite::GetDc()->BeginDraw();
				{
					mg->PostRender();
				}
				DirectWrite::GetDc()->EndDraw();

				ImGui::Render();
			}
			D2DCLASS()->Present();
		}
	}

	RenderTarget::Delete();
	DirectWrite::Delete();

	SAFE_DELETE(Time);

	SOUND->Delete();
	Input->Delete();
	
	ImGui::Delete();
	D2DCLASS()->Delete();

	mg->Release();

	delete mg;
	return msg.wParam;
}
