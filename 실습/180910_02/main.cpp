#include <iostream>
#include <vector>
using namespace std;

void main()
{
	//stl�� Ư¡
	//1. ������ ������ ũ�⸦ �������� �ʾƵ� �ȴ�.
	//2. iterator(pointer�� ����)�� ����Ѵ�.
	//3. ���ϴ� ������ ���¸� ����� �� �ִ�.

	//stl::vector
	//Ư¡: �迭�� ����ϰ� ����� �� �ִ�.

	vector<int> vInt;	//�迭�̶�� ũ�������� ��������� ���ʹ� �������

	//.push_back(data) : �����͸� �������� �ִ´�. �����Ͱ� �ڿ������� ��.
	for (int i = 0; i < 10; i++)
	{
		vInt.push_back(i);
	}

	//.begin() : ���� �ּҰ�
	vInt.begin();
	vInt.end();	//�� �ּҰ� (�����Ⱚ) << ������ �����Ͱ� �ִ� ���� �ƴ϶� �� �ٷ� ���� �ּҸ� ����Ŵ
	vInt.back();	//�������� ����ִ� ��
	//�߰� ����(.insert)
	vInt.insert(vInt.begin() + 2, 3, 50);
	//�߰� ����(.erase)
	vInt.erase(vInt.begin() + 4, vInt.begin() + 6);
	
	//������ .pop_back();
	//�ڿ��� ���� ����
	vInt.pop_back();
	vInt.pop_back();
	vInt.pop_back();

	////��ü ����
	//vInt.clear();
	
	////�̰Ŵ� vector�� ����(�ε��� ���)
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << vInt[i] << endl;
	//}
	//cout << endl;

	////.size() ���Ϳ� �� �ִ� �������� ����
	//for (int i = 0; i < vInt.size(); i++)
	//{
	//	cout << vInt[i] << endl;
	//}

	//iterator;
	vector<int>::iterator viInt;	//���� �������� ������� ����?

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