//1.���� ���� �� ���� ����� 

//�� vs ��ǻ�� 
#include <iostream>
#include <time.h>
//srand(time(NULL)) time(NULL)�� ����ϱ� ���� time.h ����

using namespace std;

void main()
{
	srand(time(NULL)); //rand() �༮�� ���� �����ϰ� �ޱ� ����

	int nSelectNum; //���� �Է��� ���ڸ� ���� 
	int nComNumber; //��ǻ�Ͱ� �����ϰ� ������ ���� ����

	int nWin = 0; //���� �̱�Ƚ��
	int nLose = 0; //���� ��ȸ�� 

	//���� �Ʒ��� ���� ���� ���� 
	for (int i = 0; i < 5; i++) //���� 5�� �ϰڴ�. 
	{
		//�ݺ��� �ȿ��� ���� 1���� �ۼ�
		//1. ���� ���ϴ� ���� ����
		cout << "����(0), ����(1), ��(2) �߿� ���� �Ͻÿ� : ";
		cin >> nSelectNum;
		//2. ��ǻ�Ͱ� ������ ���ڸ� ����
		nComNumber = rand() % 3; // 0 ~ 2
		//2_5. ������ �༮ ���
		cout << endl;

		switch (nSelectNum)
		{
		case 0:
			cout << "[�÷��̾� : ���� vs ";
			break;
		case 1:
			cout << "[�÷��̾� : ���� vs ";
			break;
		case 2:
			cout << "[�÷��̾� :  ��  vs ";
			break;
		}

		switch (nComNumber)
		{
		case 0:
			cout << "���� : ��ǻ��]" << endl;
			break;
		case 1:
			cout << "���� : ��ǻ��]" << endl;
			break;
		case 2:
			cout << " ��  : ��ǻ��]" << endl;
			break;
		}
		//3. �� , ��ǻ�� ���� ��� ���� 
		//����(0), ����(1), ��(2)
		//0 - 1, 1 - 2, 2 - (3 % 3)
		//�������
		if (nSelectNum == nComNumber)
		{
			cout << "����" << endl;
		}
		//�̰����� 
		//��ǻ�� ���� ���� +1
		else if ((nComNumber + 1) % 3 == nSelectNum)
		{
			cout << "���� �̰��." << endl;
			nWin++;
		}
		//������ 
		//
		else if ((nSelectNum + 1) % 3 == nComNumber)
		{
			cout << "���� ���� " << endl;
			nLose++;
		}
		cout << endl;
	}
	//4.�������� ����� ��� 
	cout << "�¸� : " << nWin << " �й� : " << nLose << " ��� : " <<
		5 - nWin - nLose << endl;
}