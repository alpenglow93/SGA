#pragma once //한번 인크루드 된 헤더는 읽지 않겠다. 

#include <Windows.h>
#include <assert.h> //확인용으로 사용되는 녀석 
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
	wstring AppName; //타이틀 
	HINSTANCE hInstance; // os버전
	HWND Handle; //창에 번호 정수형태
	float Width; //창의 너비 해상도 
	float Height; //창의 높이
	bool bFullScreen; //전체 혹은 창모드 
};
extern _D2DDesc desc;

//directx에서 만들어져있는 포인털를 해제 
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//내가 만든 클래스 변수 포인터 삭제시 
#define SAFE_DELETE(p) { if(p) {delete(p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p) = 0;}}