#include <iostream>
#include <string>
using namespace std;

void main()
{
	//�迭
	//�迭 �� char �������� �迭�� Ư���ϴ� -> ���ڿ�!
	char str[5] = "abcd";	//���ڿ��� �������� null���ڰ� ���� ������ [5] �迭�� 4���� ���ڱ��� ���� �� �ִ�.
	//���ڿ��� null����: ���ڿ��� ���� �˷��ִ� ������ �� "\0"
	cout << str[3] << endl;
	cout << str << endl;

	//���ڿ� �Լ�
	//1. strlen = ���ڿ��� ����
	char str1[64] = "���ڿ��� ����";	//�ѱ��� 2����Ʈ
	int length = strlen(str1);
	cout << str1 << "�� ����: " << length << endl;

	//2. strcpy = ���ڿ��� ����
	char str2[64];
	char str3[64] = "���ڿ� ����";
	//strcpy_s(������ ��, ������ ��)
	strcpy_s(str2, str3);
	cout << str2 << endl;

	//3. strcmp = ���ڿ��� ��
	char str4[64] = "abcd";
	char str5[64] = "abcd";
	char str6[64] = "abcc";
	char str7[64] = "abce";

	int result = strcmp(str4, str5);
	cout << "���ڿ��� ������: " << result << endl;

	result = strcmp(str5, str6);
	cout << "������ �� Ŭ��: " << result << endl;

	result = strcmp(str5, str7);
	cout << "�������� �� Ŭ��: " << result << endl;
	//���⼭ �� ũ�� ������ �ƽ�Ű�ڵ� ������
	cout << (int)str5[0] << endl;	//���ڿ��� int������ ���� ����ȯ
	
	//4. strcat = ���ڿ��� ��ġ��
	//A = A + B
	char str8[64] = "���ڿ� ";
	char str9[64] = "��ġ��";
	strcat_s(str8, str9);
	cout << str8 << endl;

	//5. strtok = ���ڿ��� �ڸ���
	//strtok
	//��ȯ�� -> �ڸ��� ���� ���ڿ�
	//���ڰ� _String -> ���ڿ�(����)
	//���ڰ� Delimiter(tok) -> �ڸ� Ư�� ���ڿ�
	//���ڰ� Context -> ������ ���ڿ�
	char *str10;
	char *str11;
	str10 = strtok_s(str8, "���ڿ�", &str11);
	cout << str8 << endl;
	cout << str10 << endl;
	cout << str11 << endl;
	//���̺� ������, �̹��� ȣ��
	//images/npc.png;
	//ȣ���ϴ� ��λ��� ���ϸ��� ���� ��� � ���

	//string >> Ŭ����!!
	string str12 = "string ";
	string str13 = str12 + " sum Str";
	//str12.~ �ϸ� �Լ� ����� �������� strcat �� �ش��ϴ� �Լ��� ����
	//+ �����ڷ� strcat�� ����� ������ �� �ֱ� ����
	cout << str13 << endl;
	//cout << str13.length << endl;		//��....
	cout << str13.at(4) << endl;

	string str14("String Test");
	cout << str14 << endl;
}
