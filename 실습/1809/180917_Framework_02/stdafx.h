#pragma once

#include <Windows.h>
#include <assert.h>	//확인용으로 사용되는
#include <stdio.h>	//<iostream> 과 동일한 기능을 하는 c언어 헤더
#include <vector>
#include <map>

using namespace std;

#include "./DirectX/Include/D3DX10math.h"

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