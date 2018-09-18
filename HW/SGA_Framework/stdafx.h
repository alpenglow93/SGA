#pragma once
//집에서 만들어보는 프로젝트
#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include <D3D11.h>
#include <D3DX11.h>

#include <D3DX10.h>
#include <D3DX10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")


struct _D2DDesc
{
	wstring Appname;
	HINSTANCE hInstance;
	HWND Handle;
	float Width;
	float Height;
	bool bFullScreen;
};
extern _D2DDesc desc;

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = 0; }}
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = 0; }}