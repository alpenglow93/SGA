#include <iostream>
#include <vector>
using namespace std;

void main()
{
	//stl의 특징
	//1. 저장할 데이터 크기를 지정하지 않아도 된다.
	//2. iterator(pointer의 일종)를 사용한다.
	//3. 원하는 데이터 형태를 사용할 수 있다.

	//stl::vector
	//특징: 배열과 비슷하게 사용할 수 있다.

	vector<int> vInt;	//배열이라면 크기지정을 해줬겠지만 벡터는 상관없음

	//.push_back(data) : 데이터를 마지막에 넣는다. 데이터가 뒤에서부터 들어감.
	for (int i = 0; i < 10; i++)
	{
		vInt.push_back(i);
	}

	//.begin() : 시작 주소값
	vInt.begin();
	vInt.end();	//끝 주소값 (쓰레기값) << 마지막 데이터가 있는 값이 아니라 그 바로 다음 주소를 가리킴
	vInt.back();	//마지막에 들어있는 값
	//중간 삽입(.insert)
	vInt.insert(vInt.begin() + 2, 3, 50);
	//중간 삭제(.erase)
	vInt.erase(vInt.begin() + 4, vInt.begin() + 6);
	
	//삭제는 .pop_back();
	//뒤에서 부터 삭제
	vInt.pop_back();
	vInt.pop_back();
	vInt.pop_back();

	////전체 삭제
	//vInt.clear();
	
	////이거는 vector만 가능(인덱스 출력)
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << vInt[i] << endl;
	//}
	//cout << endl;

	////.size() 벡터에 들어가 있는 데이터의 갯수
	//for (int i = 0; i < vInt.size(); i++)
	//{
	//	cout << vInt[i] << endl;
	//}

	//iterator;
	vector<int>::iterator viInt;	//위와 데이터형 맞춰야함 벡터?

	viInt = vInt.begin();
	for (viInt; viInt != vInt.end(); viInt++)
	{
		cout << (*viInt) << endl;
	}

	for (int i : vInt)
	{
		cout << "Test" << i << endl;
	}
}