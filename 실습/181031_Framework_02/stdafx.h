///�п� �ǽ�����
#pragma once

#include <Windows.h>
#include <assert.h>	//Ȯ�ο����� ���Ǵ�
#include <stdio.h>	//<iostream> �� ������ ����� �ϴ� c��� ���
#include <string>
#include <vector>
#include <map>

using namespace std;

//DirectX SDK
#include "./DirectX/Include/D3D11.h"
#include "./DirectX/Include/D3DX11.h"

#include "./DirectX/Include/D3DX10.h"
#include "./DirectX/Include/D3DX10math.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "imgui.lib")

//Singleton
#include "./System/D2D.h"
#include "./Singleton/Keyborad.h"

//Utilities
#include "./Utilities/Vertex.h"
#include "./Utilities/Util.h"

//Viewer
#include "./Viewer/Camera.h"

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
extern D3DXVECTOR3 vMouse;
extern Camera* mainCamera;	//�� ī�޶�

//dierectx���� ��������ִ� �����͸� ����
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//���� ���� Ŭ���� ���� ������ ������ ���
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[] (p); (p) = 0; }}