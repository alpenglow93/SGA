#include <iostream>
#include <string>

using namespace std;

void main()
{
	//������ Ctrl + F5
	cout << "����� ���� �ڵ� " << endl;

	//���� : ������ ������ ��(value)
	//��� : ������ �Ұ����� �� 

	//������ ����
	//������ ���� + ���� �̸�(���Ƿ� ����)
	//����(integer)�� ������ �� => int
	int nNum;
	//�Ǽ�(float)�� ������ �� => float;
	float fNum;
	//����(charactor)�� ������ �� => char
	char ch;
	//���ڿ�(string)�� ������ �� => string
	string str;
	//(�� or ����) boolean => bool
	bool check;

	//����(�ʱ�ȭ) : ������ ���� �ִ� ��
	//A = B -> B(B�� ��)�� A�� �ְڴ�.
	nNum = 20;
	fNum = 15.6f;
	ch = 'A';
	str = "���ڿ�";
	check = true;  //�� == 1;
	check = false; //���� == 0;

	cout << nNum << endl;
	cout << fNum + nNum << endl;
	nNum = 50;
	cout << nNum << endl;

	//���
	const int cnNum = 20;
	cout << cnNum << endl;

	cout << str << endl;
	//c + out , c + in
	cout << "���ϴ� ���ڸ� �Է� : ";
	cin >> nNum;
	
	cout << "�Է� �Ͻ� ���ڴ� " << nNum <<
		"�Դϴ�." << endl;

	cin >> str;
	cout << str << endl;

	int sumA;
	int sumB;
	cout << "1�� ���� :";
	cin >> sumA;
	cout << "2�� ���� :";
	cin >> sumB;

	cout << sumA << " + " <<
		sumB << " = " << sumA + sumB << endl;
	
}