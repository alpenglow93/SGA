#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//������ 

	//���� ������
	// A = B (B�� A�� �ְڴ�)
	int nNum_1 = 10;

	//��� ������
	// +, - , *, /, %(������)
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
	//�� ������ 
	// >(ũ��), <(�۴�), 
	//>=(ũ�ų� ����), <=(�۰ų� ����),
	//==(����), !=(Ʋ����)
	bool result = 10 < 4;
	cout << result << endl;

	result = 10 > 4;
	cout << result << endl;
	//�� ������ 
	//&& => and, ||(shift + \) or
	// A         &&       B
	//A(true)  && B(true) => ��  //  
	bool result2 = true && true;
	cout << result2 << endl;

	//A(true) && B(false) = ����
	result2 = true && false;
	cout << result2 << endl;

	//A(false) && B(false) => ����
	result2 = false && false;
	cout << result2 << endl;

	//or ����(||) 
	//A(true) || B(true) = > true
	result2 = true || true;
	cout << result2 << endl;

	//A(true) || B(false) => true
	result2 = true || false;
	cout << result2 << endl;

	//A(false) || B(false) = > false
	result2 = false || false;
	cout << result2 << endl;

	//���� ~ : ���ǹ�(2��), �ݺ���(2��)

	//���ǹ��� �ݺ��� ��������
	//���� ���⿡ ���ٷ� ��� �ۼ�

	//���ǹ� 2�� -> �Ӱ�, ����ۼ� ����
	//�ݺ��� 2�� -> 

	//rand() : 0 ~ 32676
	//ex) 0~ 10 = > % 11
	//ex) 1 ~ 10; => (0 ~ 9) + 1
	//ex) 7 ~ 16; => (0 ~ 9) + 7
	//ex) 0~ 10��� 100
	//    => (0~ 10) * 10
	srand(time(NULL));

	int rnd = rand() % 100;
	cout << rnd << endl;
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