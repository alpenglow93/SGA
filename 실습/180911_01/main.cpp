#include <iostream>
#include <map>
#include <string>
using namespace std;

//map


void main()
{
	//stl: 크기를 원하는대로 넣어줄 수 있다 iterator 을 이용할 수 있다 데이터형식을 마음대로 쓸 수 있다
	//map<데이터형, 데이터형> 변수명
	//1. 변수타입이 2가지 들어간다
	//2. first - key value
	//	 second - data value
	//3. 특정 상황을 제외하고 검색속도....빠름?

	map<string, int> mTest;

	//데이터 삽입
	//1.
	pair<string, int> data;
	data.first = "테스트1";
	data.second = 50;
	mTest.insert(data);
	//2.
	mTest.insert(make_pair<string, int>("테스트2", 100));
	//3. (별로 권장하지는 않는 초기화법)
	mTest["테스트3"] = 200;

	//삭제
	mTest.erase("테스트1");
	//키로 변수의 갯수 찾기
	cout << mTest.count("테스트2") << endl;
	//출력
	cout << mTest["테스트1"] << endl;
	cout << mTest.find("테스트2") ->second << endl;
	mTest.size();
	
	map<string, int>::iterator miTest;
	miTest = mTest.begin();
	for (miTest; miTest != mTest.end(); /*miTest++*/)
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

	////auto 라는 변수가 있다. 선언만은 불가능함. 선언과 동시에 초기화를 해줘야함.
	//auto iter = 0; //처음 선언할때 어떤 값으로 초기화해주느냐에 따라 데이터형을 맞춰준다
	////하지만 자주 쓰는건 권장하지는 않음.
	////일단 가독성이 떨어지고, 타인이 봤을때 코드를 알아볼 수 없음

	for (pair<string, int> p : mTest)
	{
		cout << p.first << endl;
		cout << p.second << endl;
	}
}