#pragma once //한번 인크루드 된 헤더는 읽지 않겠다. 

#include <Windows.h>
#include <assert.h> //확인용으로 사용되는 녀석 
#include <stdio.h>  //<iostream> c++,  c
#include <string>
#include <vector>
#include <map>

using namespace std;

//정적 static
//내가 선언한 위치에서 사용 가능 
//1개만 생성 가능 ,
//선언한 위치가 삭제되도 데이터 남는다.
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