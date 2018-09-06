#include <iostream>
#include <string>
using namespace std;

//구조체: 여러 데이터를 묶어서 하나의 데이터 형태로 만들어 사용하는것
//열거형(enum): 

enum STATE
{
	//초기화를 해주지 않으면 0부터 지정되지만 특정 숫자로 초기화를 해주면 다음 열거형부터는 +1 되는 방식으로 초기화가 된다
	STATE_IDLE = 10,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_DEATH,
	STATE_NONE
};	//열거형에서 해당 열거형의 이름을 붙이는 것과 대문자로 작성하는것은 암묵적인 룰

//enum TEST
//{
//	NONE
//};

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
	//state = NONE;
	//이런 경우를 막기 위해 열거형의 이름을 붙여서 구분을 지어준다
	//statd = STATE::NONE;
	//이런 식으로 쓰면 빨간줄은 없어지지만 그래도 사용은 안됨

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