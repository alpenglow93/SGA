#include <iostream>
using namespace std;


//�Լ� ������ 
void Test()
{
	cout << "Functional" << endl;
}
void Test2()
{
	cout << "Pointer" << endl;
}
void Test3(void(*fp1)(void), void(*fp2)(void))
{
	fp1();
	fp2();
}
int Test4(int num)
{
	cout << num << endl;
	return num;
}
//�Լ� �����͸� ���� ���� 
//1.���ڰ��� ������ ���°� ����
//���� ��ġ���� ���� �ϴµ� ���� �ٸ� �Լ��� 
//���۽�ų��
//2.�񵿱� �Լ��� ����� ���ؼ� 
//A -> B(����,���ѷ���) -> C 
//A -> B(�񵿱�, ���� ����) (CALLBACK �Լ�)
//  -> c
//�̺�Ʈ ó�� 
void main()
{
	void(*fp)(void);
	Test3(Test, Test2);
	int(*fp2)(int);
	fp2 = Test4;
	fp2(20);
}