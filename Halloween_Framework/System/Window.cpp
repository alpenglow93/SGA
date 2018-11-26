#include "stdafx.h"
#include "Window.h"
_D2DDesc desc;
D3DXVECTOR3 vMouse;
Camera* mainCamera; //�� ī�޶� 
Timer* Time;
LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc((UINT*)handle, message, wParam, lParam))
		return true;

	//winApi ����� ����ؼ� ���콺 ��ǥ�� �Է� ���� 
	if (message == WM_MOUSEMOVE)
	{
		vMouse.y = desc.Height - (float)HIWORD(lParam);
		vMouse.x = (float)LOWORD(lParam);
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
	//window ��� 
	WNDCLASSEX wndClass; //������ ����ü 
	wndClass.cbClsExtra = 0; //�޸� �׳� 0
	wndClass.cbWndExtra = 0; //�޸� �׳� 0
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //â�� ������ ���
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

	//assert(����)// ������ ���� ���� �ڵ���� 
	//��� ���Ͽ��� ���° ��, ������ �������� 
	assert(wHr != 0 && "Not RegisterClass");

	desc.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(), // Ŭ���� �̸�(��ϵ� Ŭ���� �̸��� ������ ���ƾ� ��)
		desc.AppName.c_str(), // Ÿ��Ʋ �̸�,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // â�� ������ġ ���� 100
		CW_USEDEFAULT, // â�� ���� ���� ��ġ 100
		CW_USEDEFAULT, // â�� ���� ũ�� 1280
		CW_USEDEFAULT, // â�� ���� ũ�� 768
		NULL,			//�θ� ������ 
		(HMENU)NULL,	//�޴�
		desc.hInstance,	
		NULL			//�Ⱦ��� �༮ 
	);

	assert(desc.Handle != NULL && "Not CreateWindow");
	RECT rc = 
	{ 0,0,(LONG)desc.Width,(LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.Height) / 2;
	//âũ�� �缳��
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	//â�̵�
	MoveWindow(
		desc.Handle,
		centerX, centerY,
		rc.right - rc.left,
		rc.bottom - rc.top,
		TRUE
	);
	//â���� 
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
	mainCamera = new Camera;
	
	mg = new MainGame;
	mg->Init();

	DirectWrite::Get();

	RenderTarget::Get(desc.Width, desc.Height);
	//���ӿ� �޼��� ���� 
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
				mainCamera->Update();
				SOUND->Update();
				mg->Update();
				ImGui::Update();
			}
			RenderTarget::Get()->SetRenderTarget();
			RenderTarget::Get()->Clear(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			{
				mainCamera->SetBuffers();
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
				mainCamera->SetBuffers();
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

	SAFE_DELETE(mainCamera);
	SAFE_DELETE(Time);

	SOUND->Delete();
	Input->Delete();
	
	ImGui::Delete();
	D2DCLASS()->Delete();

	mg->Release();

	delete mg;
	return msg.wParam;
}
