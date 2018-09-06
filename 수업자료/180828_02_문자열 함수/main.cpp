#include <iostream>
#include <string>
using namespace std;

void main()
{
	//문자열 -> NULL문자 문자열의 끝을 알려주는 녀석 
	// \0
	char str[5] = "abcd";
	cout << str[3] << endl;
	cout << str << endl;
	//문자열 함수 
	//1.strlen -> 문자열의 길이
	char str1[64] = "문자열의 길이";
	int length = strlen(str1);
	cout << str1 << "의 길이 : " << length << endl;

	//2.strcpy -> 문자열의 복사
	char str2[64];
	char str3[64] = "문자열 복사";
	//strcpy_s(복사해서 넣을 변수, 복사 당할 변수)
	strcpy_s(str2, str3);
	cout << str2 << endl;
	//3.strcmp -> 문자열의 비교
	char str4[64] = "abcd";
	char str5[64] = "abcd";
	char str6[64] = "abcc";
	char str7[64] = "abce";

	int result = strcmp(str4, str5);
	cout << "문자열이 같을때" << result << endl;

	result = strcmp(str5, str6);
	cout << "왼쪽이 더 클때" << result << endl;

	result = strcmp(str5, str7);
	cout << "오른쪽이 더 클때" << result << endl;
	//강제 형변환(int 형태로 강제로 형태 변환 시키겠다)
	cout << (int)str5[0] << endl;
	//4.strcat -> 문자열의 합치기
	//A =  A + B
	char str8[64] = "문자열 ";
	char str9[64] = "합치기";
	strcat_s(str8, str9);
	cout << str8 << endl;

	//5.strtok -> 문자열의 자르기 
	//strtok_s
	//반환값 -> 자르고 남은 문자열 
	//인자값 _String -> 문자열(원본)
	//인자값 Dellimeter (tok) -> 자를 특정 문자열 
	//인자값 Context-> 분할한 문자열 
	char* str10;
	char* str11;
	str10 = strtok_s(str8, "문자열", &str11);
	cout << str8 << endl;
	cout << str10 << endl;
	cout << str11 << endl;
	//세이브 데이터 , 이미지 호출
	//Images/npc.png;

	string str12  = "String ";
	string str13 = str12 + "sum String";

	cout << str13 << endl;

	string str14("String Test");

	cout << str14 << endl;

}