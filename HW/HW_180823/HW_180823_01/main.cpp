#include <iostream>
#include <time.h>
#include <string>
using namespace std;

void main()
{
	//���������� ���� ����

	//��ǻ�Ϳ� �÷��̾��� ���������� �����͸� ������ ����
	int nCNum;
	string sCNum;
	int nPNum;
	string sPNum;
	//���� ���� ī��Ʈ ����
	int win = 0;
	int lose = 0;
	int same = 0;

	srand(time(NULL));

	//������ �� �ټ��� ������ ���̴�
	cout << "���������� ������ �� �ټ��� ����˴ϴ�" << endl;

	for (int i = 0; i < 5; i++)
	{

		//��ǻ�Ͱ� �� ����������
		nCNum = rand() % 3;

		//�÷��̾ ���������� �Է�
		cout << i + 1 << "��° ����" << endl;
		cout << "����(0), ����(1), ��(2) �� �ش��ϴ� ���ڸ� �Է��ϰ� ���͸� ġ�ÿ�." << endl;
		cin >> nPNum;

		//����ó�� �� ���ڿ� ����
		//switch(nPNum)
		//{
		//case 0:
		//	sPNum = "����";
		//	break;
		//case 1:
		//	sPNum = "����";
		//	break;
		//case 2:
		//	sPNum = "��";
		//	break;
		//default:
		//	cout << "����(0), ����(1), ��(2) �� �ش��ϴ� �ٸ� ���ڸ� �Է��Ͻÿ�." << endl;
		//	i--;		//���������� �� Ƚ���� ġ�� �ʱ� ���� ������
		//	break;
		//}

		if (nPNum == 0 || nPNum == 1 || nPNum == 2)
		{
			switch (nPNum)
			{
			case 0:
				sPNum = "����";
				break;
			case 1:
				sPNum = "����";
				break;
			case 2:
				sPNum = "��";
				break;
				//default:
				//	cout << "����(0), ����(1), ��(2) �� �ش��ϴ� �ٸ� ���ڸ� �Է��Ͻÿ�." << endl;
				//	i--;		//���������� �� Ƚ���� ġ�� �ʱ� ���� ������
				//	break;
			}


			switch (nCNum)
			{
			case 0:
				sCNum = "����";
				break;
			case 1:
				sCNum = "����";
				break;
			case 2:
				sCNum = "��";
				break;
			}

			cout << "��ǻ�Ͱ� �� ��: " << sCNum << endl;
			cout << "�÷��̾ �� ��: " << sPNum << endl;

			//��� ��
			if (nCNum == nPNum)
			{
				cout << "�����ϴ�" << endl << endl;
				same++;
			}
			else if (nCNum == 0)	//��ǻ�Ͱ� ����
			{
				if (nPNum == 1)	//�÷��̾ ����
				{
					cout << "�����ϴ�" << endl << endl;
					lose++;
				}
				else	//nPNum ==2 //�÷��̾ ��
				{
					cout << "�̰���ϴ�" << endl << endl;
					win++;
				}
			}
			else if (nCNum == 1)	//��ǻ�Ͱ� ����
			{
				if (nPNum == 0)	//�÷��̾ ����
				{
					cout << "�����ϴ�" << endl << endl;
					lose++;
				}
				else	//nPNum == 2 //�÷��̾ ��
				{
					cout << "�̰���ϴ�" << endl << endl;
					win++;
				}
			}
			else	//nCNum == 2	//��ǻ�Ͱ� ��
			{
				if (nPNum == 0)	//�÷��̾ ����
				{
					cout << "�̰���ϴ�" << endl << endl;
					win++;
				}
				else	//nPNum == 1	//�÷��̾ ����
				{
					cout << "�����ϴ�" << endl << endl;
					lose++;
				}
			}
		}
		else
		{
			cout << "����(0), ����(1), ��(2) �� �ش��ϴ� �ٸ� ���ڸ� �Է��Ͻÿ�." << endl;
			i--;		//���������� �� Ƚ���� ġ�� �ʱ� ���� ������
		}

		//0 1 2 �� �ƴ� ���ڸ� �Է��� ��� �Ʒ����� �۾��� �����ϸ� �ȵ�



		//�׽�Ʈ���
		//cout << nCNum << endl;

	}

	cout << "�̱� Ƚ��: " << win << endl;
	cout << "�� Ƚ��: " << lose << endl;
	cout << "��� Ƚ��: " << same << endl;

}