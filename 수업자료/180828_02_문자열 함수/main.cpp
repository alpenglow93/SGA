#include <iostream>
#include <string>
using namespace std;

void main()
{
	//���ڿ� -> NULL���� ���ڿ��� ���� �˷��ִ� �༮ 
	// \0
	char str[5] = "abcd";
	cout << str[3] << endl;
	cout << str << endl;
	//���ڿ� �Լ� 
	//1.strlen -> ���ڿ��� ����
	char str1[64] = "���ڿ��� ����";
	int length = strlen(str1);
	cout << str1 << "�� ���� : " << length << endl;

	//2.strcpy -> ���ڿ��� ����
	char str2[64];
	char str3[64] = "���ڿ� ����";
	//strcpy_s(�����ؼ� ���� ����, ���� ���� ����)
	strcpy_s(str2, str3);
	cout << str2 << endl;
	//3.strcmp -> ���ڿ��� ��
	char str4[64] = "abcd";
	char str5[64] = "abcd";
	char str6[64] = "abcc";
	char str7[64] = "abce";

	int result = strcmp(str4, str5);
	cout << "���ڿ��� ������" << result << endl;

	result = strcmp(str5, str6);
	cout << "������ �� Ŭ��" << result << endl;

	result = strcmp(str5, str7);
	cout << "�������� �� Ŭ��" << result << endl;
	//���� ����ȯ(int ���·� ������ ���� ��ȯ ��Ű�ڴ�)
	cout << (int)str5[0] << endl;
	//4.strcat -> ���ڿ��� ��ġ��
	//A =  A + B
	char str8[64] = "���ڿ� ";
	char str9[64] = "��ġ��";
	strcat_s(str8, str9);
	cout << str8 << endl;

	//5.strtok -> ���ڿ��� �ڸ��� 
	//strtok_s
	//��ȯ�� -> �ڸ��� ���� ���ڿ� 
	//���ڰ� _String -> ���ڿ�(����)
	//���ڰ� Dellimeter (tok) -> �ڸ� Ư�� ���ڿ� 
	//���ڰ� Context-> ������ ���ڿ� 
	char* str10;
	char* str11;
	str10 = strtok_s(str8, "���ڿ�", &str11);
	cout << str8 << endl;
	cout << str10 << endl;
	cout << str11 << endl;
	//���̺� ������ , �̹��� ȣ��
	//Images/npc.png;

	string str12  = "String ";
	string str13 = str12 + "sum String";

	cout << str13 << endl;

	string str14("String Test");

	cout << str14 << endl;

}