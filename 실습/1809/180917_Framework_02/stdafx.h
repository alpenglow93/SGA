#pragma once

#include <Windows.h>
#include <assert.h>	//Ȯ�ο����� ���Ǵ�
#include <stdio.h>	//<iostream> �� ������ ����� �ϴ� c��� ���
#include <vector>
#include <map>

using namespace std;

#include "./DirectX/Include/D3DX10math.h"

//static: ����~~		���� ������ �ʴ´�
//���� ������ ��ġ���� ��� ����
//1���� ���� ����
//������ ��ġ�� ����(â�� ����ɶ�, ������ ������)�Ǵ��� �����ʹ� ���´�
struct _D2DDesc
{
	wstring AppName;		//������ Ÿ��Ʋ �̸�
	HINSTANCE hInstance;	//os ����
	HWND Handle;			//â�� ��ȣ�� �ٿ���(��������)
	//hinstance �� handle �� �츮�� �������ִ°� �ƴ϶� ��ǻ�Ͱ� �����ϴ°�
	float Width;			//â�� �ʺ�
	float Height;			//â�� ���� -> �ػ�
	bool bFullScreen;		//��üȭ�� or â���
};
extern _D2DDesc desc;