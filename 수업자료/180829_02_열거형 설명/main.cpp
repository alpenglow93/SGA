#include <iostream>
#include <string>
using namespace std;

//구조체 : 여러 데이터를 묶어서 하나의 데이터 형태로 만들어 사용
//열거형(enum) : 

enum STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_ATTACK = 10,
	STATE_DEATH,
	STATE_NONE
};
enum TEST
{
	NONE
};

struct tagCharactor
{
	string ID;
	char pass[64];
	float hp;
	float mp;
	int att;
	int def;
	bool death;
};

void main()
{

	STATE state;

	state = STATE_NONE;


	tagCharactor player;
	player.ID = "Id";
	player.hp = 100.0f;
	player.mp = 100.0f;
	player.att = 10;
	player.def = 5;
	player.death = false;

	tagCharactor monster;
	monster.ID = "monster";
	monster.hp = 50;
	//....

	cout << player.ID << endl;


	switch (state)
	{
	case STATE_IDLE:

		break;
	case STATE_MOVE:

		break;
	case STATE_ATTACK:

		break;
	case STATE_DEATH:

		break;
	case STATE_NONE:
		break;
	default:
		break;
	}
}