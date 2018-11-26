#include "stdafx.h"
#include "String.h"



///////////////////////////////////////////////////////////////////////////////////////
///@brief 문자열 자르기 
///@param origin : 원본 문자열
///@param tok : 자를 기준이 되는 문자열
///@return 완료된 문자열 벡터
///////////////////////////////////////////////////////////////////////////////////////
void String::SplitString(OUT vector<string>* result, IN string origin, IN string tok)
{
	result->clear();
	int cutAt = 0; //자를 위치
	//string.npos -> 마지막 위치 
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크면 
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은 것이 있다면 
		result->push_back(origin.substr(0, cutAt));

}

void String::SplitString(OUT vector<wstring>* result, IN wstring origin, IN wstring tok)
{
	result->clear();
	int cutAt = 0; //자를 위치
				   //string.npos -> 마지막 위치 
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다 크면 
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은 것이 있다면 
		result->push_back(origin.substr(0, cutAt));
}


///////////////////////////////////////////////////////////////////////////////////////
///@brief 시작 문자열이 같은지 확인
///@param str : 원본 문자열
///@param comp : 시작 비교 문자열
///////////////////////////////////////////////////////////////////////////////////////
BOOL String::StartsWith(IN string str, string comp)
{
	string::size_type index = str.find(comp);
	if (index != string::npos && (int)index == 0)
		return TRUE;

	return FALSE;
}

BOOL String::StartsWith(IN wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return TRUE;

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////
//@brief 해당 문자열이 포함되어 있는지 확인
//@param str : 원본 문자열
//@param comp : 비교 문자열
//////////////////////////////////////////////////////////////////////////////////////
BOOL String::Contain(IN string str, IN string comp)
{
	size_t found = str.find(comp);

	return found != string::npos;
}

BOOL String::Contain(IN wstring str, IN wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}


///////////////////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열에서 comp문자를 rep로 변경
///@param str : 원본 문자열
///@param comp : 비교 문자열
///@param rep : 바꿀 문자열
///////////////////////////////////////////////////////////////////////////////////////
VOID String::Replace(IN OUT string * str, IN string comp, IN string rep)
{
	string temp = *str;
	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != string::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}
	*str = temp;
}

VOID String::Replace(IN OUT wstring * str, IN wstring comp, IN wstring rep)
{
	wstring temp = *str;
	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}
	*str = temp;
}


///////////////////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열 타입을 변경
///@param value : 변환할 문자열
///@return : 변환 완료 문자열
///////////////////////////////////////////////////////////////////////////////////////
wstring String::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());
	return temp;
}

string String::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());
	return temp;
}

