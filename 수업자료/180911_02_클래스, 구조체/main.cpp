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
		//생성자 
	}
	~tagUint()
	{
		//소멸자 
	}
	virtual void Function() = 0;
};
struct tagMonster : public tagUint
{
private:

public:
	void Function() override;
};


//구조체(public), 클래스(private) 차이점 
//1. 기본 접근 지정자 
void main()
{
	//typedef : 사용자 지정 데이터 형 
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