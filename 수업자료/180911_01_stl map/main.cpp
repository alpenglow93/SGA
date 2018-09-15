#include <iostream>
#include <map>
#include <string>

using namespace std;

void main()
{
	//stl
	//map<데이터형, 데이터형> 변수명  
	//1. 변수 타입 2가지 들어간다.
	//2. first - key value 
	// . second - data value
	//3. 특정 상황을 제외하고 검색속도 

	map<string, int> mTest;
	
	//데이터 삽입
	//1. 
	pair<string, int> data;
	data.first = "테스트1";
	data.second = 50;
	mTest.insert(data);
	//2.
	mTest.insert(
		make_pair<string, int>("테스트2", 100));

	//3.
	mTest["테스트3"] = 200;
	
	//삭제
	mTest.erase("테스트1");
	//키로 변수의 갯수 찾기?
	cout << mTest.count("테스트2") << endl;
	//출력
	cout << mTest["테스트1"] << endl;
	cout << mTest.find("테스트2")->second 
		<< endl;
	mTest.size();

	map<string, int>::iterator miTest;
	miTest = mTest.begin();
	for (miTest; miTest != mTest.end();)
	{
		if (miTest->second != 0)
		{
			miTest = mTest.erase(miTest);
		}
		else
		{
			miTest++;
		}
		//cout << miTest->first << endl;
		//cout << miTest->second << endl;
	}
	mTest.clear();

	//auto iter = mTest.begin();
	for (pair<string, int> p : mTest)
	{
		cout << p.first << endl;
		cout << p.second << endl;
	}

}