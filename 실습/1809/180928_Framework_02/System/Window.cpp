#include "stdafx.h"
#include "Window.h"
_D2DDesc desc;
D3DXVECTOR3 vMouse;

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	//winAPI ����� ����ؼ� ���콺 ��ǥ�� �Է� ����
	if (message == WM_MOUSEMOVE)
	{
		vMouse.y = desc.Height - (float)HIWORD(lParam);
		vMouse.x = (float)LOWORD(lParam);
	}
	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);	//��ǻ�Ϳ��� 0 �̶�� �޽����� ����
		//0 -> �޸𸮸� �����϶�
		//�̰� ������� ������ â�� ���� ���μ������� ������ ����
		//���μ������� ����ϰ� �ֱ� ������ ���ٰ� �ٽ� �Ѵ°� ���� �ʴ´�

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
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//�귯�� ��׶���. â�� ��ĥ�ϴ°�. (â�� ������ �������)
	//ũ�� �߿������� �ʴ�. �ֳ��ϸ� ���۹��� ��������Ŷ�.
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);	//winlogo: �⺻ â��� ������
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//hIconSm: �̸����� ��� ������ ����������
	wndClass.hInstance = desc.hInstance;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	//2byte
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);

	//assert(����) //������ ������ ��� �����ڵ� ����
	//��� ���Ͽ��� ���° ��, ������ ��������
	assert(wHr != 0 && "Not RegisterClass");

	desc.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(),	//Ŭ���� �̸�(��ϵ� Ŭ���� �̸��� �Ȱ��ƾ���)
		desc.AppName.c_str(),	//Ÿ��Ʋ �̸�
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,	//â�� ���� ���� ��ġ 100
		CW_USEDEFAULT,	//â�� ���� ���� ��ġ 100
		CW_USEDEFAULT,	//â�� ���� ũ�� 1280
		CW_USEDEFAULT,	//â�� ���� ũ�� 768
		//CW_USEDEFAULT: �⺻��
		NULL,			//�θ�������
		(HMENU)NULL,	//�޴�
		desc.hInstance,
		NULL			//�� ���� �༮
	);

	assert(desc.Handle != NULL && "Not CreateWindow");
	RECT rc = { 0, 0, (LONG)desc.Width, (LONG)desc.Height };

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

	//static int x = 100, y = 100;

	
	//HDC hdc = GetDC(desc.Handle);	//���� ����
	//HDC memDC = CreateCompatibleDC(hdc);	//����� //�̹��� ����
	//HBITMAP hBit;	//�̹���
	//hBit = (HBITMAP)CreateCompatibleBitmap(
	//	memDC, desc.Width, desc.Height);	//�� �̹���
	//HBITMAP hOBit = (HBITMAP)SelectObject(memDC, hBit);	//�̹��� ������ �ʿ�

	//d2d = new D2D;
	
	mg = new MainGame;
	mg->Init();

	//���ӿ� �޼��� ����
	while (1)
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
			//���ӵ���
			//Update();
			//Render();

			//	//Ű�Է�
			//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			//	{
			//		x -= 1;
			//		//InvalidateRect(desc.Handle, NULL, true);
			//	}
			//	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			//	{
			//		x += 1;
			//		//InvalidateRect(desc.Handle, NULL, true);
			//	}

			//	//����
			//	//������� ������ �������
			//PatBlt(memDC, 0, 0, desc.Width, desc.Height, WHITENESS);
			//	//����ۿ� ������ �׸���
			//	Rectangle(memDC, x, y, x + 100, y + 100);
			//	//������� ������ ������۷� ������
			//	BitBlt(hdc, 0, 0, desc.Width, desc.Height, memDC, 0, 0, SRCCOPY);


			//	//HDC hdc = GetDC(desc.Handle);
			//	//Rectangle(hdc, x, y, x + 100, y + 100);
			//	//ReleaseDC(desc.Handle, hdc);

			//R G B A (0.0f ~ 1.0f)
			//d2d->Clear(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			//{

			//}
			//d2d->Present();
			mg->Update();
			D2DCLASS()->Clear(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			{
				mg->Render();
			}
			D2DCLASS()->Present();
		}
	}
	//ReleaseDC(desc.Handle, memDC);
	//ReleaseDC(desc.Handle, hdc);
	Input->Delete();
	D2DCLASS()->Delete();
	mg->Release();
	//SAFE_DELETE(mg); <<��������
	delete mg;

	return msg.wParam;
}
