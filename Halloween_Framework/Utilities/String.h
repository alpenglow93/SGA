#pragma once
class String
{
public:
	static VOID SplitString(OUT vector<string>* result, IN string origin, IN string tok);
	static VOID SplitString(OUT vector<wstring>* result, IN wstring origin, IN wstring tok);

	static BOOL StartsWith(IN string str, string comp);
	static BOOL StartsWith(IN wstring str, wstring comp);

	static BOOL Contain(IN string str, IN string comp);
	static BOOL Contain(IN wstring str, IN wstring comp);

	static VOID Replace(IN OUT string* str, IN string comp, IN string rep);
	static VOID Replace(IN OUT wstring* str, IN wstring comp, IN wstring rep);

	static wstring ToWString(string value);
	static string ToString(wstring value);
};

