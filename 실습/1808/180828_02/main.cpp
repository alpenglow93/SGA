#include <iostream>
#include <string>
using namespace std;

void main()
{
	//배열
	//배열 중 char 데이터형 배열은 특이하다 -> 문자열!
	char str[5] = "abcd";	//문자열의 마지막은 null문자가 들어가기 때문에 [5] 배열에 4개의 문자까지 넣을 수 있다.
	//문자열의 null문자: 문자열의 끝을 알려주는 역할을 함 "\0"
	cout << str[3] << endl;
	cout << str << endl;

	//문자열 함수
	//1. strlen = 문자열의 길이
	char str1[64] = "문자열의 길이";	//한글은 2바이트
	int length = strlen(str1);
	cout << str1 << "의 길이: " << length << endl;

	//2. strcpy = 문자열의 복사
	char str2[64];
	char str3[64] = "문자열 복사";
	//strcpy_s(복사할 곳, 복사할 것)
	strcpy_s(str2, str3);
	cout << str2 << endl;

	//3. strcmp = 문자열의 비교
	char str4[64] = "abcd";
	char str5[64] = "abcd";
	char str6[64] = "abcc";
	char str7[64] = "abce";

	int result = strcmp(str4, str5);
	cout << "문자열이 같을때: " << result << endl;

	result = strcmp(str5, str6);
	cout << "왼쪽이 더 클때: " << result << endl;

	result = strcmp(str5, str7);
	cout << "오른쪽이 더 클때: " << result << endl;
	//여기서 더 크고 작은건 아스키코드 기준임
	cout << (int)str5[0] << endl;	//문자열을 int형으로 강제 형변환
	
	//4. strcat = 문자열의 합치기
	//A = A + B
	char str8[64] = "문자열 ";
	char str9[64] = "합치기";
	strcat_s(str8, str9);
	cout << str8 << endl;

	//5. strtok = 문자열의 자르기
	//strtok
	//반환값 -> 자르고 남은 문자열
	//인자값 _String -> 문자열(원본)
	//인자값 Delimiter(tok) -> 자를 특정 문자열
	//인자값 Context -> 분할한 문자열
	char *str10;
	char *str11;
	str10 = strtok_s(str8, "문자열", &str11);
	cout << str8 << endl;
	cout << str10 << endl;
	cout << str11 << endl;
	//세이브 데이터, 이미지 호출
	//images/npc.png;
	//호출하는 경로상의 파일명을 쓰는 경우 등에 사용

	//string >> 클래스!!
	string str12 = "string ";
	string str13 = str12 + " sum Str";
	//str12.~ 하면 함수 목록이 나오지만 strcat 에 해당하는 함수는 없다
	//+ 연산자로 strcat의 기능을 수행할 수 있기 때문
	cout << str13 << endl;
	//cout << str13.length << endl;		//음....
	cout << str13.at(4) << endl;

	string str14("String Test");
	cout << str14 << endl;
}
