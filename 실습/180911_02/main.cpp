#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

struct tagUint
{
	int dat;
	float angle;
	tagUint()	//����ü �ȿ��� ������ ���� ����
	{

	}
	~tagUint()
	{
		//�Ҹ��ڵ� ����
	}
	void Function()
	{
		//�Ϲ� �Լ��� ����
	}

};
struct tagMonster : public tagUint
{
	//����ü���� ��ӵ� ����
	//�����Լ��� ����
	//���������Լ��� ����
	//�����ε嵵 ����
private:
public:
	//���������� ��뵵 ����
};

void main()
{
	//typedef: ����� ���� ��������
	typedef int Data;	//Data��� �̸��� ������ int�� ����� �ϰ� �ȴ�
	typedef vector<int> vInt;	//vInt��� �̸��� ������ vector�� ����� �ϰ� �ȴ�

	Data test;
	vInt test2;
	test2.push_back(0);
	test2.pop_back();

	//������ ���� ����ü���� ���� ��
	typedef struct tagPlayer
	{
		int hp;
		int mp;
		int att;
		int def;
	}Player, *LPPlayer;		//���� �̸� ����, �ڿ����� �������� ��� ������ �̸�

	tagPlayer player1;
	Player Player2;

	tagPlayer* pPlayer1 = new Player;
	Player* pPlayer2 = new Player;
	LPPlayer pPlayer3 = new Player;
}