#include <iostream>
using namespace std;

//����Ǯ��
//�� ���

void ShowStar(int num, char ch[6])
{
	cout << ch[num];
	if (num < 0) return;
	ShowStar(num - 1, ch);	//��� �Լ�: �Լ� ���ο��� �ڱ� �ڽ��� ����ϴ°�
}
void ShowSpace(int num, char ch[6])
{
	if (num > 4) return;
	cout << ch[num];
	ShowSpace(num + 1, ch);
}
void Test(int n)	//����Լ� ȣ��� ���� ������ �����ֱ� ���� �׽�Ʈ �Լ�
{
	cout << n << ": ��� �Լ� ��" << endl;
	if (n > 0) Test(n - 1);
	cout << n << ": ��� �Լ� ��" << endl;
}
void main()
{
	//Test(5);
	char star[6] = "*****";
	char space[6] = "     ";
	cout << star[5] << "Test" << endl;
	for (int i = 0; i < strlen(star) - 1; i++)
	{
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = strlen(star); i > 0; i--)
	{
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = strlen(star); i > 0; i--)
	{
		ShowSpace(i + 1, space);
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = 0; i < strlen(star); i++)
	{
		ShowSpace(i, space);
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = 0; i < strlen(star); i++)
	{
		cout << star + i << endl;
	}

	for (int i = 0; i < strlen(star); i++)
	{
		cout << star + i << endl;
	}
	for (int i = strlen(star) - 1; i >= 0; i--)
	{
		cout << star + i << endl;
	}
	for (int i = 0; i < strlen(star); i++)
	{
		cout << space + i;
		cout << star + (strlen(star) - i) << endl;
	}

	//���� �߸� ���̴ּٰ� �մϴ�
	//������ ���ڿ� �����⸦ �߾����

	char str[64] = "abcdefg";

	for (int i = strlen(str); i >= 0; i--)
		cout << str[i];
	cout << endl;
}