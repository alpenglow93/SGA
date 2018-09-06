#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void ShowCard(int shape, int number)
{
	switch (shape)
	{
	case 0:
		cout << "��";
		break;
	case 1:
		cout << "��";
		break;
	case 2:
		cout << "��";
		break;
	case 3:
		cout << "��";
		break;
	}
	//tab -> space bar * 8�� 
	//���� ����(\t tap�� ���� ��ŭ �̵�) 
	switch (number)
	{
	case 0:
		cout << "A \t";
		break;
	case 10:
		cout << "J \t";
		break;
	case 11:
		cout << "Q \t";
		break;
	case 12:
		cout << "K \t";
		break;
	default:
		cout << number + 1 << " \t";
		break;
	}
}

void main()
{
	srand(time(NULL));

	int card[52];		//ī�� �� 52��
	int shape[3];		//ȭ�鿡 ������ ī�� 3���� ���
	int number[3];		//ȭ�鿡 ������ ī�� 3���� ����

	int dest, sour, temp; // ���ÿ� ����

	int betting;		//���ÿ� ����(�Է¿�)
	int money = 10000;  //������
	int turn = 0;		//����� ī�带 ������ ����, ���߿� 3���߰�
	int gameCount = 0;  //���� ī��Ʈ

	//ī�� �ʱ�ȭ
	for (int i = 0; i < 52; i++)
	{
		card[i] = i;				//0~51;
	}
	//����
	for (int i = 0; i < 999; i++)
	{
		dest = rand() % 52;
		sour = rand() % 52;

		temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}
	//���� �����
	while (true)
	{
		for (int i = 0; i < 3; i++)
		{
			shape[i] = card[i + turn] / 13; //���� 
			number[i] = card[i + turn] % 13; //���� 

			if (i == 2) cout << "ġƮ : ";
			//��� ����
			ShowCard(shape[i], number[i]);
			//0  + 0, 1 + 0 , 2 + 0 -> 0 ,1 ,2
			//0  + 3, 1 + 3 , 2 + 3 -> 3 ,4 ,5
		}
		cout << endl;

		//�� �ݾ��� �����ְ� ���ñݾ� �Է� �ޱ�
		cout << "������ : " << money << endl;
		cout << "�������� : ";
		cin >> betting;

		//�� ���� �ݾ��� 1000 �̸��̶�� ���� 
		if (money < 1000)
		{
			cout << "�Ļ�!!!! �λ���!!!!" << endl;
			Sleep(1000);   //1�ʰ� �����̸� ��
			break;
		}
		
		//���� �ݾ��� 1000�̸� �Ǵ� ������ ���� ���� ��� �ٽ� ����
		if (1000 > betting || betting > money)
		{
			cout << "�ٽ� �����ض�!!" << endl;
			Sleep(1000);
			continue;
		}

		//�˻� 
		//C��° ī�� -> A B����
		//A < C < B , B < C < A

		if (number[0] < number[1])
		{
			int temp = number[0];
			number[0] = number[1];
			number[1] = temp;
		}
		//if(number[1] < number[2] && number[2] < number[0] ||
		//number[0] < number[2] && number[2] < number[1] )
		if (number[1] < number[2] && number[2] < number[0])
		{
			cout << "ī�� ���� : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money += betting;
			cout << betting << "�� ȹ��" << endl;
			Sleep(1000);
		}
		else
		{
			cout << "ī�� ���� : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money -= betting;
			cout << betting << "�� ���� " << endl;
			Sleep(1000);
		}
		system("cls");
		turn += 3;//����� ī�� ������
		gameCount++; //���� ī��Ʈ ����
		if (gameCount == 17)
		{
			cout << "�� �̻� ī�尡 ���� " << endl;
			Sleep(1000);
			break;
		}
	}
}