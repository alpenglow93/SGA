#include <iostream>
using namespace std;


//�Լ�(function): �̸� �ڵ带 �ۼ��س��� ������ ���� ��
//��ȯ�� �Լ���(�Ű�����)
//��ȯ��(��������)	�Լ���(���������� ���´�)

void Function1(void)
{
	cout << "�Լ� �׽�Ʈ " << endl;
}
void Function2(int num)
{
	cout << "�Ű����� �׽�Ʈ: " << num << endl;
}
int SumNumber(int num1, int num2)
{
	int result = num1 + num2;
	return result;
}
//call by value(���� ���� ȣ��) -> ����
void Sum(int result, int num1, int num2)
{
	result = num1 + num2;
	cout << "�Լ� ���� ���: " << result << endl;
}
//�Լ� ���漱��: �Լ��� �����Ѵٴ� ���� ��ǻ�Ϳ� �̸� �˷��ְ�, �Լ� ������ �Ʒ��� ���ش�
float Mul(float num1, float num2);
float Mul(float num1);
float Mul(int num1);
//int Mul(int num1);
//�Լ� �����ε�(OverLoading): �Լ� �̸��� ���Ƶ� �Ű������� ���ϰ��� ���̿� ���� �ٸ� �Լ��� �ν��ϴ� ���. ������ �Լ��� ���������� �ٸ����� ������� �ʴ´�.
//�Լ��� �̸��� ���� �Լ� ���ڰ��� �ٸ� �Լ����� �ٸ� �Լ��� �ν��ϴ� ��� -> ����

void main()
{
	//����� �ڵ�� ������ main �ȿ��� �ۼ�
	for (int i = 0; i < 2; i++)
	{
		Function1();
	}
	Function2(200);
	int nNumber = 400;
	Function2(nNumber);
	int nNumber2 = SumNumber(100, 200);
	cout << nNumber2 << endl;
	int nResult = 0, nNum1 = 10, nNum2 = 20;
	Sum(nResult, nNum1, nNum2);
	cout << "�Լ� ���� �� ��갪: " << nResult << endl;
	
	float fNum = Mul(10.25f, 4.6f);
	float fNum2 = Mul(24.0f);
	cout << fNum << endl;
	//����...�� ���ٴµ� �� �� ���ٳ�.. ���� ����� �ȵǴµ�.
	//�ƹ�ư ������ ���� ������ �ڵ�� ���������� �о���� ������ Mul �Լ��� �ִ��� �𸣱� ������ ������ ����
	//zz������������ �ù� �̰� c++�̶� �׷���
}
float Mul(float num1, float num2)
{
	return num1 * num2;
}
float Mul(float num1)	
{
	return num1 * 100;
}