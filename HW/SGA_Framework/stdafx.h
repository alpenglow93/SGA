#pragma once

#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

#include "DirectX/Include/D3DX10math.h"

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