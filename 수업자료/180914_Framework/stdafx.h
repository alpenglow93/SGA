#pragma once //�ѹ� ��ũ��� �� ����� ���� �ʰڴ�. 

#include <Windows.h>
#include <assert.h> //Ȯ�ο����� ���Ǵ� �༮ 
#include <stdio.h>  //<iostream> c++,  c
#include <string>
#include <vector>
#include <map>

using namespace std;

//���� static
//���� ������ ��ġ���� ��� ���� 
//1���� ���� ���� ,
//������ ��ġ�� �����ǵ� ������ ���´�.
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