#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

struct tagUint
{
	int data;
	float angle;
	tagUint()
	{
		//������ 
	}
	~tagUint()
	{
		//�Ҹ��� 
	}
	virtual void Function() = 0;
};
struct tagMonster : public tagUint
{
private:

public:
	void Function() override;
};


//����ü(public), Ŭ����(private) ������ 
//1. �⺻ ���� ������ 
void main()
{
	//typedef : ����� ���� ������ �� 
	typedef int Data;
	typedef vector<int> vInt;

	Data test;
	vInt test2;
	test2.push_back(0);
	test2.pop_back();

	typedef struct tagPlayer
	{
		int hp;
		int mp;
		int att;
		int def;
	}Player, *LPPlayer;
	
	tagPlayer player1;
	Player player2;

	tagPlayer* pPlayer1 = new Player;
	Player* pPlayer2 = new Player;
	LPPlayer pPlayer3 = new Player;
}