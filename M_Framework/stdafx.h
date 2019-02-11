#pragma once //한번 인크루드 된 헤더는 읽지 않겠다. 

#include <Windows.h>
#include <assert.h> //확인용으로 사용되는 녀석 
#include <stdio.h>  //<iostream> c++,  c
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

//DirectWrite
#include <d2d1_1.h>
#include <dwrite.h>
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

//DirectX SDK
#include <dxgi1_2.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <D3DX10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxguid.lib")



//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "imgui.lib")

//System
#include "./System/D2D.h"
#include "./System/Timer.h"
#include "./System/Xml.h"
#include "./System/DirectWrite.h"

//Singleton
#include "./Singleton/Keyboard.h"
#include "./Singleton/Sound.h"

//Utilities
#include "./Utilities/Vertex.h"
#include "./Utilities/Util.h"
#include "./Utilities/String.h"

//Renderer
#include "./Render/Shader.h"
#include "./Render/Sprite.h"
#include "./Render/RenderTarget.h"

struct _D2DDesc
{
	wstring AppName; //타이틀 
	HINSTANCE hInstance; // os버전
	HWND Handle; //창에 번호 정수형태
	float Width; //창의 너비 해상도 
	float Height; //창의 높이
	bool bFullScreen; //전체 혹은 창모드 
	bool bVsync; //수직동기화 
};

//WindowToggle
extern bool bInsfacter;
extern bool bWorldOutlinear;

//extern
extern _D2DDesc desc;
extern D3DXVECTOR3 vMouse;
extern Timer* Time;


//Path
const wstring _Texture = L"../_Resources/Textures/";
const wstring _Shader = L"../_Resources/Shader/";
const wstring _Sound = L"../_Resources/Sound/";

const wstring _MapleAvatar = L"../_Resources/Textures/Maple/Avatar/";

//directx에서 만들어져있는 포인털를 해제 
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//내가 만든 클래스 변수 포인터 삭제시 
#define SAFE_DELETE(p) { if((p)) {delete(p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p) = 0;}}