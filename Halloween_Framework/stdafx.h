#pragma once //�ѹ� ��ũ��� �� ����� ���� �ʰڴ�. 

#include <Windows.h>
#include <assert.h> //Ȯ�ο����� ���Ǵ� �༮ 
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

//Renderer
#include "./Render/Shader.h"
#include "./Render/Sprite.h"


//Viewer
#include "./Viewer/Camera.h"
struct _D2DDesc
{
	wstring AppName; //Ÿ��Ʋ 
	HINSTANCE hInstance; // os����
	HWND Handle; //â�� ��ȣ ��������
	float Width; //â�� �ʺ� �ػ� 
	float Height; //â�� ����
	bool bFullScreen; //��ü Ȥ�� â��� 
	bool bVsync; //��������ȭ 
};
extern _D2DDesc desc;
extern D3DXVECTOR3 vMouse;
extern Camera* mainCamera; //�� ī�޶� 
extern Timer* Time;

const wstring Textures = L"./Textures/";

//directx���� ��������ִ� �����и� ���� 
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//���� ���� Ŭ���� ���� ������ ������ 
#define SAFE_DELETE(p) { if((p)) {delete(p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p) = 0;}}