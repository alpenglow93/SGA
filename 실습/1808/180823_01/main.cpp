#include <iostream>
using namespace std;

void main()
{
	//���ǹ�: Ư�������� �����ϰų� �Ҹ����� �ٸ� �ڵ带 �����ϰڴ�.

	//if, switch

	//if( ���� ) ���� -> ���ϰ�� 
	//{
	//	������ ���ϰ�� {} ������ �ڵ带 ����
	//}
	//else
	//{
	//	������ �����϶� {} ������ �ڵ带 ����
	//}

	int nNum1 = 10;
	int nNum2 = 10;

	if (nNum1 > nNum2)
	{
		cout << nNum1 << "�� " << nNum2 << "���� Ů�ϴ�." << endl;
		//c++��� ����� ��¹��
	}
	else if (nNum1 == nNum2)
	{
		cout << nNum1 << "�� " << nNum2 << "�� ���� �����ϴ�." << endl;
	}
	else if (nNum1 < 0)
	{
		cout << nNum1 << "�� 0���� �۽��ϴ�." << endl;
	}
	else
	{
		printf("%d�� %d���� �۽��ϴ�. \n", nNum1, nNum2);
		//c��� ����� ��¹��
	}

	//switch( ���� )
	//{
	//	case ������ ���� �� �ִ� ��:
	//	break;
	//	case ������ ���� �� �ִ� ��:
	//	break;
	//	case ������ ���� �� �ִ� ��:
	//	break;
	//	case ������ ���� �� �ִ� ��:
	//	break;
	//}

	char ch;
	
	ch = 'd';

	//cout << "���� �Է�" << endl;
	//cin >> ch;

	//break -> {} �� ���������� ��ɾ�
	//�ݺ���(for, while), switch;

	switch (ch)
	{
	case 'a':
		cout << "�������� �̵�" << endl;
		break;
	case 'd':
		cout << "���������� �̵�" << endl;
		break;
	case 'w':
		cout << "�������� �̵�" << endl;
		break;
	case 's':
		cout << "�Ʒ������� �̵�" << endl;
		break;
	default:	//��õ� ���̽� ���� ������ �༮�� ������ ���Ե�����
		cout << "�߸� �Է��Ͽ����ϴ�" << endl;
		break;
	}

	int nNum3 = 4;
	switch(nNum3)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		cout << "���" << endl;
		break;
	default:
		break;
	}
	//����
	if (0 <= nNum3 && nNum3 < 4)
	{
		cout << "���" << endl;
	}
	//�ǹ�

	if (0 <= nNum3)
	{
		if (nNum3 < 4)
		{
			cout << "���" << endl;
		}
	}

	//1.
	cout << "=================" << endl;
	int nSumNum = 5;

	nSumNum = nSumNum + 1;

	cout << nSumNum << endl;

	//
	nSumNum += 1;
	cout << nSumNum << endl;

	nSumNum *= 2;
	cout << nSumNum << endl;

	bool bCheck = true;
	bCheck &= false;
	bCheck |= true;

	//+1 -1
	nSumNum++;
	cout << nSumNum << endl;	//15
	
	//++nSumNum�� nSumNum++ �� ����
	cout << ++nSumNum << endl;
	//1 ���� �� ȭ�鿡 ���

	cout << nSumNum++ << endl;
	//��� �� 1 ����
	cout << nSumNum << endl;
}