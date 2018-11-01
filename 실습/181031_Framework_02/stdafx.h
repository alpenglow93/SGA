///학원 실습파일
#pragma once

#include <Windows.h>
#include <assert.h>	//확인용으로 사용되는
#include <stdio.h>	//<iostream> 과 동일한 기능을 하는 c언어 헤더
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

//static: 정적~~		값이 변하지 않는다
//내가 선언한 위치에서 사용 가능
//1개만 생성 가능
//선언한 위치가 삭제(창이 종료될때, 게임이 꺼질때)되더라도 데이터는 남는다
struct _D2DDesc
{
	wstring AppName;		//윈도우 타이틀 이름
	HINSTANCE hInstance;	//os 버전
	HWND Handle;			//창에 번호를 붙여줌(정수형태)
	//hinstance 와 handle 은 우리가 지정해주는게 아니라 컴퓨터가 지정하는것
	float Width;			//창의 너비
	float Height;			//창의 높이 -> 해상도
	bool bFullScreen;		//전체화면 or 창모드
};
extern _D2DDesc desc;
extern D3DXVECTOR3 vMouse;
extern Camera* mainCamera;	//주 카메라

//dierectx에서 만들어져있는 포인터를 해제
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//내가 만든 클래스 변수 포인터 삭제시 사용
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[] (p); (p) = 0; }}