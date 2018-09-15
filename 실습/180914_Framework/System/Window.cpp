#include "stdafx.h"
#include "./System/Window.h"


LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);	//��ǻ�Ϳ��� 0 �̶�� �޽����� ����
		//0 -> �޸𸮸� �����϶�
		//�̰� ������� ������ â�� ���� ���μ������� ������ ����
		//���μ������� ����ϰ��ֱ� ������ ���ٰ� �ٽ� �Ѵ°� ���� �ʴ´�
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

Window::Window()
{
	//window ���
	WNDCLASSEX wndClass;	//������ ����ü
	wndClass.cbClsExtra = 0;	//�޸� 0����
	wndClass.cbWndExtra = 0;	//�޸� 0
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//�귯����׶���. â�� ��ĥ�ϴ°�
	//â�� ������ �������
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);	//winlogo: �⺻ â��� ������
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//hIconSm: �̸������� ������ ����������
	wndClass.hInstance = desc.hInstance;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	//2byte
	WORD wHr = RegisterClassEx(&wndClass);

	//assert(����)// ������ ������ ��� �����ڵ� ����
	//��� ���Ͽ��� ���° ��, ������ ��������
	assert(wHr != 0 && "Not RegisterClass");

	desc.Handle = CreateWindowEx(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(),	//Ŭ���� �̸�(��ϵ� Ŭ���� �̸��� �Ȱ��ƾ���)
		desc.AppName.c_str(),	//Ÿ��Ʋ �̸�
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,	//â�� ���� ���� ��ġ 100
		CW_USEDEFAULT,	//â�� ���� ���� ��ġ 100
		CW_USEDEFAULT,	//â�� ���� ũ�� 1280
		CW_USEDEFAULT,	//â�� ���� ũ�� 768
		//CW_USEDEFAULT �⺻��
		NULL,			//�θ� ������
		(HMENU)NULL,	//�޴�
		desc.hInstance,
		NULL			//�� ���� �༮
	);

	assert(desc.Handle != NULL && "Not CreateWindow");
	RECT rc =
	{ 0, 0, (LONG)desc.Width, (LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	//SM_CXSCREEN: ������� ���κκ�
	//����� ���ο��� ���� �κ��� ���ְڴ�
	UINT centerY = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Height) / 2;
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

	//���ӿ� �޼��� ����
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
			//���������� ���� �����ϴ� ����
			//Update();
			//Render();
		}
	}
	return msg.wParam;
}
