#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

struct tagUint
{
	int dat;
	float angle;
	tagUint()	//구조체 안에서 생성자 생성 가능
	{

	}
	~tagUint()
	{
		//소멸자도 가능
	}
	void Function()
	{
		//일반 함수도 가능
	}

};
struct tagMonster : public tagUint
{
	//구조체끼리 상속도 가능
	//가상함수도 가능
	//순수가상함수도 가능
	//오버로드도 가능
private:
public:
	//접근지정자 사용도 가능
};

void main()
{
	//typedef: 사용자 지정 데이터형
	typedef int Data;	//Data라는 이름의 변수는 int의 기능을 하게 된다
	typedef vector<int> vInt;	//vInt라는 이름의 변수는 vector의 기능을 하게 된다

	Data test;
	vInt test2;
	test2.push_back(0);
	test2.pop_back();

	//하지만 보통 구조체에서 많이 씀
	typedef struct tagPlayer
	{
		int hp;
		int mp;
		int att;
		int def;
	}Player, *LPPlayer;		//새로 이름 지정, 뒤에것은 포인터일 경우 지정한 이름

	tagPlayer player1;
	Player Player2;

	tagPlayer* pPlayer1 = new Player;
	Player* pPlayer2 = new Player;
	LPPlayer pPlayer3 = new Player;
}