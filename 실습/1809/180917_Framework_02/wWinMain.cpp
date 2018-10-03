#pragma once
#include "stdafx.h"
#include "./System/Window.h"
int WINAPI WinMain(
	HINSTANCE instance,
	HINSTANCE prevInstance,
	LPSTR param,
	int command
)
{
	//������ ������ ����?
	//������ �����ؾ� �ȴ�.

	//���� -> �����̳� ���� ���
	//���� -> Ư�� ������ ��ġ, ȸ��, ũ��
	//�� -> ī�޶�
	//���� -> ���� ����(2D), ���� ����(3D)
	//����Ʈ -> â�� ũ��

	desc.AppName = L"D2D Game";
	desc.hInstance = instance;
	desc.bFullScreen = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;

	Window* window = new Window();

	//HDC hdc = GetDC(desc.Handle);
	//Rectangle(hdc, 100, 100, 200, 200);
	//ReleaseDC(desc.Handle, hdc);

	WPARAM wParam = window->Run();
	delete window;

	return wParam;
}