#include "stdafx.h"
#include "String.h"



///////////////////////////////////////////////////////////////////////////////////////
///@brief ���ڿ� �ڸ��� 
///@param origin : ���� ���ڿ�
///@param tok : �ڸ� ������ �Ǵ� ���ڿ�
///@return �Ϸ�� ���ڿ� ����
///////////////////////////////////////////////////////////////////////////////////////
void String::SplitString(OUT vector<string>* result, IN string origin, IN string tok)
{
	result->clear();
	int cutAt = 0; //�ڸ� ��ġ
	//string.npos -> ������ ��ġ 
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�� 
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ� 
		result->push_back(origin.substr(0, cutAt));

}

void String::SplitString(OUT vector<wstring>* result, IN wstring origin, IN wstring tok)
{
	result->clear();
	int cutAt = 0; //�ڸ� ��ġ
				   //string.npos -> ������ ��ġ 
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�� 
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ� 
		result->push_back(origin.substr(0, cutAt));
}


///////////////////////////////////////////////////////////////////////////////////////
///@brief ���� ���ڿ��� ������ Ȯ��
///@param str : ���� ���ڿ�
///@param comp : ���� �� ���ڿ�
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
//@brief �ش� ���ڿ��� ���ԵǾ� �ִ��� Ȯ��
//@param str : ���� ���ڿ�
//@param comp : �� ���ڿ�
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
///@brief �ش� ���ڿ����� comp���ڸ� rep�� ����
///@param str : ���� ���ڿ�
///@param comp : �� ���ڿ�
///@param rep : �ٲ� ���ڿ�
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
///@brief �ش� ���ڿ� Ÿ���� ����
///@param value : ��ȯ�� ���ڿ�
///@return : ��ȯ �Ϸ� ���ڿ�
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

