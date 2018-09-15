#include <iostream>
#include <map>
#include <string>

using namespace std;

void main()
{
	//stl
	//map<��������, ��������> ������  
	//1. ���� Ÿ�� 2���� ����.
	//2. first - key value 
	// . second - data value
	//3. Ư�� ��Ȳ�� �����ϰ� �˻��ӵ� 

	map<string, int> mTest;
	
	//������ ����
	//1. 
	pair<string, int> data;
	data.first = "�׽�Ʈ1";
	data.second = 50;
	mTest.insert(data);
	//2.
	mTest.insert(
		make_pair<string, int>("�׽�Ʈ2", 100));

	//3.
	mTest["�׽�Ʈ3"] = 200;
	
	//����
	mTest.erase("�׽�Ʈ1");
	//Ű�� ������ ���� ã��?
	cout << mTest.count("�׽�Ʈ2") << endl;
	//���
	cout << mTest["�׽�Ʈ1"] << endl;
	cout << mTest.find("�׽�Ʈ2")->second 
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