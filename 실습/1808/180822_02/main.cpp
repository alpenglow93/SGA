#include <iostream>
#include <time.h>
//time �̶� �ĺ��ڸ� ����ϱ� ���� ����

using namespace std;

void main()
{
	//������

	//���Կ�����
	// A = B (B�� A�� �ְڴ�)
	int nNum_1 = 10;

	//���������
	// +, -, *, /, %(������)
	int nNum_2 = 20;
	int nNum_3 = 8;
	int nNum_4;

	nNum_4 = nNum_2 + nNum_3;
	cout << nNum_4 << endl;

	nNum_4 = nNum_3 * nNum_1 - nNum_2;
	cout << nNum_4 << endl;

	nNum_4 = nNum_3 * (nNum_1 - nNum_2);
	cout << nNum_4 << endl;

	nNum_4 = nNum_2 / nNum_3;
	cout << nNum_4 << endl;
	nNum_4 = nNum_2 % nNum_3;
	cout << nNum_4 << endl;
	
	//�񱳿�����(���迬����)
	// >(ũ��), <(�۴�), >=(ũ�ų� ����), <=(�۰ų� ����), ==(����), !=(�ٸ���)
	bool result = 10 < 4;
	cout << result << endl;
	result = 10 > 4;
	cout << result << endl;

	//��������
	// && => and, || => or

	// A	&&		B
	//A(ture) && B(true) => ��
	bool result2 = true && true;
	cout << result2 << endl;
	//A(true) && B(false) => ����
	result2 = true && false;
	cout << result2 << endl;
	//A(false) && B(false) => ����
	result2 = false && false;
	cout << result2 << endl;
	//�� ��� ���̾�� ��

	//or ����(||)
	//A		||		B
	//A(ture) || B(true) => ture
	result2 = true || true;
	cout << result2 << endl;
	//A(true) || B(false) => true
	result2 = true || false;
	cout << result2 << endl;
	//A(false) || B(false) => false
	result2 = false || false;
	cout << result2 << endl;
	//�� �� �ϳ��� ���̸� ��

	//���� ~: ���ǹ�, �ݺ��� (���� �ΰ���)
	//���ǹ��� �ݺ��� ��������
	//���ǹ��̶� ~~~�̴�
	//�ݺ����̶� ~~~�̴�
	//���� ���⿡ ���ٷ� ��� �ۼ� << ī�信 �ۼ�

	//���ǹ� 2���� �������� ��� �ۼ��� �ϴ���
	//�ݺ����� ��������
	//�̰� ī�信 �� �÷��� �ǰ� ���������� ����



	///////////////////////////

	//rand(): 0~32676 ������ ���ڰ� �����ϰ� ����
	//�׷����� ��� �����ص� ���� ���� ����

	//ex) 0~10 �� ���ڸ� ������ �ϰ� �ʹٸ�
	//cout << rand() % 11 << endl;
	//�̷� ������ 11�� �������� ���ϴ� ���� ���ٿ��ָ� ��

	//ex) 1~10 �� ���ڸ� ������ �ϰ� �ʹ�
	//(0 ~ 9) + 1
	//cout << rand() % 10 + 1 << endl;

	//ex) 7~16 �� ���ڸ� ������ �ϰ� �ʹ�
	// (0 ~ 9) + 7
	//ex) 0 ~ 10�� ����� ������ �ϰ� �ʹ� 100
	//(0 ~ 10) * 10

	srand(time(NULL));
	//�̰� ����ϸ� �����Ҷ����� ���ݾ� ���ڰ� ����
	//�ѹ��� ��������� ����� �� �������ڰ� ������ ��

	cout << endl << endl;

	int rnd = rand() % 100;
	cout << rnd << endl;

	cout << endl << endl;

	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	
}