#include <iostream>
#include <time.h>

using namespace std;

void main()
{
	//���� ���ھ߱�
	//�迭 �������ְ� ��Ų�� ���� �迭 �̿��ϴ°� ���Ѱ���

	int answer[3];	//��ǻ�Ͱ� �������� ���� (����)���ڸ� �����ϴ� ����
	int cnt = 0;	//10���� ��ȸ ī��Ʈ
	int input_value[3] = { 0, 0, 0 };	//�÷��̾ �Է��� ���ڸ� �����ϴ� ����
	int temp;

	//���ӿ� �ʿ��� �μ�
	int strike = 0;
	int ball = 0;
	int out = 0;

	while (1)
	{
		//��ǻ�Ͱ� �������� ���ڸ� ����
		srand(time(NULL));
		answer[0] = rand() % 10;
		answer[1] = rand() % 10;
		answer[2] = rand() % 10;

		//�׽�Ʈ���
		//cout << "��ǻ�Ͱ� �������� �� ��(�׽�Ʈ���): " << answer[0] << " " << answer[1] << " " << answer[2] << endl;

		//�� ���Ͱ� �ߺ����� ������ �� ������ (����)
		//�׷��� ��ǻ�Ͱ� ���� ���� �ߺ����� üũ�� �� �ߺ��� ������ �� ���ö����� �������� �̴°� �ݺ�.

		if (answer[0] != answer[1] && answer[0] != answer[2] && answer[1] != answer[2])
			break;
	}

	//10���� ��ȸ
	for (cnt = 0; cnt < 10; cnt++)
	{
		strike = 0;
		ball = 0;
		out = 0;

		cout << "���� ������ �Է��Ͻÿ�" << endl;
		cin >> temp;
		input_value[0] = temp / 100;
		//cout << "�׽�Ʈ ���: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		temp = temp - (input_value[0] * 100);
		//cout << "�׽�Ʈ ���: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		input_value[1] = temp / 10;
		//cout << "�׽�Ʈ ���: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		temp = temp - (input_value[1] * 10);
		//cout << "�׽�Ʈ ���: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		input_value[2] = temp;
		//cout << "�׽�Ʈ ���: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;

		//���� ��
		//answer[], input_value[]
		for (int i = 0; i < 3; i++)
		{
			if (answer[i] == input_value[i])
			{
				strike++;
			}
			else if (answer[i] == input_value[0] || answer[i] == input_value[1] || answer[i] == input_value[2])
			{
				ball++;
			}
			else
			{
				out++;
			}
		}

		cout << "strike: " << strike << endl;
		cout << "ball: " << ball << endl;
		cout << "out: " << out << endl << endl;
		cout << "���� ��ȸ: " << 9 - cnt << "��" << endl << endl;

		if (strike == 3)
			break;

	}

	if (strike == 3)
	{
		cout << "����!" << endl << "���� �¸�!" << endl;
	}
	else
	{
		cout << "10���� ���� ��ȸ�� ��� ����" << endl << "���� ����" << endl;
	}
}