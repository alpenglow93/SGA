#include <iostream>
#include <vector>

using namespace std;

void main()
{
	//stl 특징 
	//1.저장할 데이터 크기를 지정하지 않아도 된다.
	//2.iterator(pointer의 일종)를 사용한다.
	//3.원하는 데이터 형태를 사용할수 있다. 

	//stl::vector,   기하학 벡터(방향, 힘)

	//특징 : 배열과 비슷하게 사용할수 있다. 

	vector<int> vInt;

	//.push_back(data) : 데이터를 마지막에 넣는다.
	for (int i = 0; i < 10; i++)
	{
		vInt.push_back(i);
	}

	//.begin() //시작 주소값 
	vInt.begin();
	vInt.end(); // 끝주소값 (쓰레기값)
	vInt.back(); //마지막에 들어 있는 값
	//중간 삽입(.insert)
	vInt.insert(vInt.begin() + 2, 3, 50);
	//중간 삭제(.erase)
	vInt.erase(vInt.begin() + 4, vInt.begin() + 6);
	//삭제는 .pop_back();
	//뒤에서 부터 삭제 
	vInt.pop_back();
	vInt.pop_back();
	vInt.pop_back();

	//전체 삭제 
	//vInt.clear();

	//.size() 벡터에 들어가 있는 데이터의 갯수 
	//이거는 vector만 가능
	//for (int i = 0; i < vInt.size(); i++)
	//	cout << vInt[i] << endl;

	//iterator;
	vector<int>::iterator viInt;

	viInt = vInt.begin();
	for (viInt; viInt != vInt.end(); viInt++)
	{
		cout << (*viInt) << endl;
	}
	//for each()
	for (int i : vInt)
	{
		cout << "Test" << i << endl;
	}
}