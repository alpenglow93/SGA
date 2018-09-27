#pragma once //�ѹ� ��ũ��� �� ����� ���� �ʰڴ�. 

#include <Windows.h>
#include <assert.h> //Ȯ�ο����� ���Ǵ� �༮ 
#include <stdio.h>  //<iostream> c++,  c
#include <string>
#include <vector>
#include <map>

using namespace std;

//DirectX SDK
#include <d3d11.h>
#include <d3dX11.h>
#include <d3dX10.h>
#include <d3dX10math.h>

#pragma comment(lib, "./DirectX/Lib/x86/d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//Singleton
#include "./System/D2D.h";

//Utilities
#include "./Utilities/Vertex.h"

struct _D2DDesc
{
	wstring AppName; //Ÿ��Ʋ 
	HINSTANCE hInstance; // os����
	HWND Handle; //â�� ��ȣ ��������
	float Width; //â�� �ʺ� �ػ� 
	float Height; //â�� ����
	bool bFullScreen; //��ü Ȥ�� â��� 
};
extern _D2DDesc desc;

//directx���� ��������ִ� �����и� ���� 
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//���� ���� Ŭ���� ���� ������ ������ 
#define SAFE_DELETE(p) { if(p) {delete(p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p) = 0;}}